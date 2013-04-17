// Use the SysTick timer to request interrupts at a particular period.

// oscilloscope or LED connected to PD0 for period measurement
#include "SysTickInts.h"
#include "lm3s1968.h"
#include "ADC.h"
#include "UART.h"
#include "Main.h"


#define NVIC_SYS_PRI3_R         (*((volatile unsigned long *)0xE000ED20))  // Sys. Handlers 12 to 15 Priority
#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))
#define NVIC_ST_CTRL_CLK_SRC    0x00000004  // Clock Source
#define NVIC_ST_CTRL_INTEN      0x00000002  // Interrupt enable
#define NVIC_ST_CTRL_ENABLE     0x00000001  // Counter mode
#define GPIO_PORTD_DIR_R        (*((volatile unsigned long *)0x40007400))
#define GPIO_PORTD_DEN_R        (*((volatile unsigned long *)0x4000751C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC2_GPIOD      0x00000008  // port D Clock Gating Control

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode
#define GPIO_PORTG2             (*((volatile unsigned long *)0x40026010))

// **************SysTick_Init*********************
// Initialize Systick periodic interrupts
// Input: interrupt period
//        Units of period are 20ns
//        Maximum is 2^24-1
//        Minimum is determined by length of ISR
// Output: none
void SysTick_Init(unsigned long period){
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOG;
	delay(10);
	GPIO_PORTG_DIR_R &= 0x07;
	GPIO_PORTG_DIR_R |= 0x04;
	GPIO_PORTG_AFSEL_R |= 0xF8;
	GPIO_PORTG_PUR_R |= 0xF8;
	GPIO_PORTG_DEN_R |= 0xFF;
	NVIC_ST_CTRL_R = 0;         // disable SysTick during setup
  NVIC_ST_RELOAD_R = period-1;// reload value
  NVIC_ST_CURRENT_R = 0;      // any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000; // priority 2
                              // enable SysTick with core clock and interrupts
  NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE+NVIC_ST_CTRL_CLK_SRC+NVIC_ST_CTRL_INTEN;
}

// Interrupt service routine
// Executed every 20ns*(period)
void SysTick_Handler(void){char* inData;
	GPIO_PORTG2 ^= 0x04;
	ADCMail = ADC_In();
	inData = convert((int)ADCMail);
	GPIO_PORTG2 ^= 0x04;
	UART_OutChar(2);
	UART_OutString(inData);
	UART_OutChar(' ');
	UART_OutChar(3);
	ADCStatus = 1;
	GPIO_PORTG2 ^= 0x04;        // toggle Pg2
}

