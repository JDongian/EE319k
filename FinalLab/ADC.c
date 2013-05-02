#include "ADC.h"
#include "globals.h"
#include "inc/hw_types.h"
#include "inc/lm3s1968.h"
#include "Control.h"

#define ADC_ACTSS_R             (*((volatile unsigned long *)0x40038000))
#define ADC0_RIS_R              (*((volatile unsigned long *)0x40038004))
#define ADC0_IM_R               (*((volatile unsigned long *)0x40038008))
#define ADC0_ISC_R              (*((volatile unsigned long *)0x4003800C))
#define ADC0_EMUX_R             (*((volatile unsigned long *)0x40038014))
#define ADC0_SSPRI_R            (*((volatile unsigned long *)0x40038020))
#define ADC0_PSSI_R             (*((volatile unsigned long *)0x40038028))
#define ADC0_SSMUX3_R           (*((volatile unsigned long *)0x400380A0))
#define ADC0_SSCTL3_R           (*((volatile unsigned long *)0x400380A4))
#define ADC0_SSFIFO3_R          (*((volatile unsigned long *)0x400380A8))
#define ADC_ACTSS_ASEN3         0x00000008  // ADC SS3 Enable
#define ADC_RIS_INR3            0x00000008  // SS3 Raw Interrupt Status
#define ADC_IM_MASK3            0x00000008  // SS3 Interrupt Mask
#define ADC_ISC_IN3             0x00000008  // SS3 Interrupt Status and Clear
#define ADC_EMUX_EM3_M          0x0000F000  // SS3 Trigger Select mask
#define ADC_EMUX_EM3_PROCESSOR  0x00000000  // Processor (default)
#define ADC_SSPRI_SS3_4TH       0x00003000  // fourth priority
#define ADC_SSPRI_SS2_3RD       0x00000200  // third priority
#define ADC_SSPRI_SS1_2ND       0x00000010  // second priority
#define ADC_SSPRI_SS0_1ST       0x00000000  // first priority
#define ADC_PSSI_SS3            0x00000008  // SS3 Initiate
//#define ADC_SSMUX3_MUX0_M       0x00000003  // 1st Sample Input Select mask
#define ADC_SSMUX3_MUX0_S       0           // 1st Sample Input Select lshift
#define ADC_SSCTL3_TS0          0x00000008  // 1st Sample Temp Sensor Select
#define ADC_SSCTL3_IE0          0x00000004  // 1st Sample Interrupt Enable
#define ADC_SSCTL3_END0         0x00000002  // 1st Sample is End of Sequence
#define ADC_SSCTL3_D0           0x00000001  // 1st Sample Diff Input Select
#define ADC_SSFIFO3_DATA_M      0x000003FF  // Conversion Result Data mask
#define SYSCTL_RCGC0_R          (*((volatile unsigned long *)0x400FE100))
#define SYSCTL_RCGC0_ADC        0x00010000  // ADC0 Clock Gating Control
#define SYSCTL_RCGC0_ADCSPD_M   0x00000300  // ADC Sample Speed mask
#define SYSCTL_RCGC0_ADCSPD125K 0x00000000  // 125K samples/second

// This initialization function sets up the ADC according to the
// following parameters.  Any parameters not explicitly listed
// below are not modified:
// Max sample rate: <=125,000 samples/second
// Sequencer 0 priority: 1st (highest)
// Sequencer 1 priority: 2nd
// Sequencer 2 priority: 3rd
// Sequencer 3 priority: 4th (lowest)
// SS3 triggering event: software trigger
// SS3 1st sample source: programmable using variable 'channelNum' [0:3]
// SS3 interrupts: enabled but not promoted to controller

volatile unsigned int ADCStatus0=0;
volatile unsigned long ADCValue0=0;
volatile unsigned long ADCSum0=0;
volatile unsigned int sampleNumber0=0;
volatile unsigned int ADCStatus1=0;
volatile unsigned long ADCValue1=0;
volatile unsigned long ADCSum1=0;
volatile unsigned int sampleNumber1=0;

void ADC_InitSWTriggerSeq3(unsigned char channelNum){
  // channelNum must be 0-3 (inclusive) corresponding to ADC0 through ADC3
  if(channelNum > 3){
    return;                                 // invalid input, do nothing
  }
  // **** general initialization ****
  SYSCTL_RCGC0_R |= SYSCTL_RCGC0_ADC;       // activate ADC
  SYSCTL_RCGC0_R &= ~SYSCTL_RCGC0_ADCSPD_M; // clear ADC sample speed field
  SYSCTL_RCGC0_R += SYSCTL_RCGC0_ADCSPD125K;// configure for 125K ADC max sample rate (default setting)
  // **** ADC initialization ****
                                            // sequencer 0 is highest priority (default setting)
                                            // sequencer 1 is second-highest priority (default setting)
                                            // sequencer 2 is third-highest priority (default setting)
                                            // sequencer 3 is lowest priority (default setting)
  ADC0_SSPRI_R = (ADC_SSPRI_SS0_1ST|ADC_SSPRI_SS1_2ND|ADC_SSPRI_SS2_3RD|ADC_SSPRI_SS3_4TH);
  ADC_ACTSS_R &= ~ADC_ACTSS_ASEN3;          // disable sample sequencer 3
  ADC0_EMUX_R &= ~ADC_EMUX_EM3_M;           // clear SS3 trigger select field
  ADC0_EMUX_R += ADC_EMUX_EM3_PROCESSOR;    // configure for software trigger event (default setting)
  ADC0_SSMUX3_R &= ~ADC_SSMUX3_MUX0_M;      // clear SS3 1st sample input select field
                                            // configure for 'channelNum' as first sample input
  ADC0_SSMUX3_R += (channelNum<<ADC_SSMUX3_MUX0_S);
  ADC0_SSCTL3_R = (0                        // settings for 1st sample:
                   & ~ADC_SSCTL3_TS0        // read pin specified by ADC0_SSMUX3_R (default setting)
                   | ADC_SSCTL3_IE0         // raw interrupt asserted here
                   | ADC_SSCTL3_END0        // sample is end of sequence (default setting, hardwired)
                   & ~ADC_SSCTL3_D0);       // differential mode not used (default setting)
  ADC0_IM_R &= ~ADC_IM_MASK3;               // disable SS3 interrupts (default setting)
  ADC_ACTSS_R |= ADC_ACTSS_ASEN3;           // enable sample sequencer 3
}

// This function triggers an ADC conversion using sample
// sequencer 3, waits for the conversion to finish, and returns
// the result in the lower 10 bits of the return value.  It
// assumes that the hardware has already been initialized
// using ADC_InitSWTriggerSeq3().
unsigned long ADC_In0(void){
  unsigned long currentADC;
	ADC0_PSSI_R = ADC_PSSI_SS3;									// initiate SS3
  while((ADC0_RIS_R&ADC_RIS_INR3)==0){};			// wait for conversion done
  currentADC = ADC0_SSFIFO3_R&ADC_SSFIFO3_DATA_M;
  ADC0_ISC_R = ADC_ISC_IN3;										// acknowledge completion of current conversion
	return currentADC;
}
unsigned long ADC_In1(void){
  unsigned long currentADC;
	ADC0_PSSI_R = ADC_PSSI_SS3;									// initiate SS3
  while((ADC0_RIS_R&ADC_RIS_INR3)==0){};			// wait for conversion done
  currentADC = ADC0_SSFIFO3_R&ADC_SSFIFO3_DATA_M;
  ADC0_ISC_R = ADC_ISC_IN3;										// acknowledge completion of current conversion
  return currentADC;
}

//debug cohis program periodically samples ADC channel 0 and stores the
// result to a global variable that can be accessed with the JTAG
// debugger and viewed with the variable watch feature.
#define NVIC_EN0_INT19          0x00080000  // Interrupt 19 enable
#define NVIC_EN0_R              (*((volatile unsigned long *)0xE000E100))  // IRQ 0 to 31 Set Enable Register
#define NVIC_PRI4_R             (*((volatile unsigned long *)0xE000E410))  // IRQ 16 to 19 Priority Register
#define TIMER0_CFG_R            (*((volatile unsigned long *)0x40030000))
#define TIMER0_TAMR_R           (*((volatile unsigned long *)0x40030004))
#define TIMER0_CTL_R            (*((volatile unsigned long *)0x4003000C))
#define TIMER0_IMR_R            (*((volatile unsigned long *)0x40030018))
#define TIMER0_ICR_R            (*((volatile unsigned long *)0x40030024))
#define TIMER0_TAILR_R          (*((volatile unsigned long *)0x40030028))
#define TIMER0_TAPR_R           (*((volatile unsigned long *)0x40030038))
#define TIMER_CFG_16_BIT        0x00000004  // 16-bit timer configuration,
                                            // function is controlled by bits
                                            // 1:0 of GPTMTAMR and GPTMTBMR
#define TIMER_TAMR_TAMR_PERIOD  0x00000002  // Periodic Timer mode
#define TIMER_CTL_TAEN          0x00000001  // GPTM TimerA Enable
#define TIMER_IMR_TATOIM        0x00000001  // GPTM TimerA Time-Out Interrupt
                                            // Mask
#define TIMER_ICR_TATOCINT      0x00000001  // GPTM TimerA Time-Out Raw
                                            // Interrupt
#define TIMER_TAILR_TAILRL_M    0x0000FFFF  // GPTM TimerA Interval Load
                                            // Register Low
#define GPIO_PORTC_DATA_R       (*((volatile unsigned long *)0x400063FC))
#define GPIO_PORTC_DIR_R        (*((volatile unsigned long *)0x40006400))
#define GPIO_PORTC_DEN_R        (*((volatile unsigned long *)0x4000651C))
#define SYSCTL_RCGC1_R          (*((volatile unsigned long *)0x400FE104))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC1_TIMER0     0x00010000  // timer 0 Clock Gating Control
#define SYSCTL_RCGC2_GPIOC      0x00000004  // port C Clock Gating Control

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

// This debug function initializes Timer0A to request interrupts
// at a 10 Hz frequency.  It is similar to FreqMeasure.c.
void Timer0B_Init10HzInt(void){
  volatile unsigned long delay;
  DisableInterrupts();
  // **** general initialization ****
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_TIMER0;// activate timer0
  delay = SYSCTL_RCGC1_R;          // allow time to finish activating
  TIMER0_CTL_R &= ~TIMER_CTL_TBEN; // disable timer0A during setup
  TIMER0_CFG_R = TIMER_CFG_16_BIT; // configure for 16-bit timer mode
  // **** timer0A initialization ****
                                   // configure for periodic mode
  TIMER0_TBMR_R = TIMER_TBMR_TBMR_PERIOD;
  TIMER0_TBPR_R = 9;               // prescale value for 10 Hz interrupts
  TIMER0_TBILR_R = 60000;          // start value for 10 Hz interrupts
  TIMER0_IMR_R |= TIMER_IMR_TBTOIM;// enable timeout (rollover) interrupt
  TIMER0_ICR_R = TIMER_ICR_TBTOCINT;// clear timer0A timeout flag
  TIMER0_CTL_R |= TIMER_CTL_TBEN;  // enable timer0A 16-b, periodic, interrupts
  // **** interrupt initialization ****
                                   // Timer0A=priority 2
  NVIC_PRI5_R = (NVIC_PRI5_R&0xFFFFFF0F)|0x00000020; // top 3 bits
  NVIC_EN0_R |= NVIC_EN0_INT20;    // enable interrupt 19 in NVIC
  EnableInterrupts();
}

void Timer1B_Init10HzInt(void){
  volatile unsigned long delay;
  DisableInterrupts();
  // **** general initialization ****
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_TIMER0;// activate timer0
  delay = SYSCTL_RCGC1_R;          // allow time to finish activating
  TIMER0_CTL_R &= ~TIMER_CTL_TBEN; // disable timer0A during setup
  TIMER0_CFG_R = TIMER_CFG_16_BIT; // configure for 16-bit timer mode
  // **** timer0A initialization ****
                                   // configure for periodic mode
  TIMER0_TBMR_R = TIMER_TBMR_TBMR_PERIOD;
  TIMER0_TBPR_R = 9;               // prescale value for 10 Hz interrupts
  TIMER0_TBILR_R = 60000;          // start value for 10 Hz interrupts
  TIMER0_IMR_R |= TIMER_IMR_TBTOIM;// enable timeout (rollover) interrupt
  TIMER0_ICR_R = TIMER_ICR_TBTOCINT;// clear timer0A timeout flag
  TIMER0_CTL_R |= TIMER_CTL_TBEN;  // enable timer0A 16-b, periodic, interrupts
  // **** interrupt initialization ****
                                   // Timer0A=priority 2
  NVIC_PRI5_R = (NVIC_PRI5_R&0xFF0FFFFF)|0x00200000; // top 3 bits
  NVIC_EN0_R |= NVIC_EN0_INT22;    // enable interrupt 19 in NVIC
  EnableInterrupts();
}

void Timer0B_Handler(void){
  TIMER0_ICR_R = TIMER_ICR_TBTOCINT;			// acknowledge timer0B timeout
  //GPIO_PORTG_DATA_R |= 0x40;            // turn on LED
  ADCValue0 = ADC_In0();
	ADCStatus0 = 1;
  ADCValue1 = ADC_In1();
	ADCStatus1 = 1;
	updateXAxis();
	updateYAxis();
  //GPIO_PORTG_DATA_R &= ~0x40;           // turn off LED
}

void Timer1B_Handler(void){
  TIMER0_ICR_R = TIMER_ICR_TBTOCINT;			// acknowledge timer0B timeout
  //GPIO_PORTG_DATA_R |= 0x40;            // turn on LED
//  ADCValue1 = ADC_In1();
//	ADCStatus1 = 1;
  //GPIO_PORTG_DATA_R &= ~0x40;           // turn off LED
}
void ADC_Init(void){
  ADC_InitSWTriggerSeq3(2);             // allow time to finish activating
  Timer0B_Init10HzInt();                // set up Timer0A for 10 Hz interrupts
	//Timer1B_Init10HzInt();                // set up Timer0A for 10 Hz interrupts
}

unsigned long getADC0Value(void) {
	return ADCValue0;
}
unsigned long getADC1Value(void) {
	return ADCValue1;
}
