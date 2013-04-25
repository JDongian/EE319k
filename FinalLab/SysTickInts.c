// Use the SysTick timer to request interrupts at a particular period.

// oscilloscope or LED connected to PD0 for period measurement
#include "SysTickInts.h"
#include "Main.h"
#include "rit128x96x4.h"
#include "Delay.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

int inData=0;
long sum=0;
int sample=0;
void SysTick_IntEnable(void) {
	NVIC_ST_CTRL_R |= NVIC_ST_CTRL_INTEN;
}

// **************SysTick_Init*********************
// Initialize Systick periodic interrupts
// Input: interrupt period
//        Units of period are 20ns
//        Maximum is 2^24-1
//        Minimum is determined by length of ISR
// Output: none
void SysTick_Init(unsigned long period){
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOG;
	doNothing();
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
  NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE+NVIC_ST_CTRL_CLK_SRC;
}

// Interrupt service routine
// Executed every 20ns*(period)
void SysTick_Handler(void){
	GPIO_PORTG2 ^= 0x04;
	if(HWREGBITW(&gFlags, FRAME_BUFFER_READY) == 1) {
		RIT128x96x4ImageDraw(getBuffer(), 0, 0, 128, 96);	//draw it.(dude!!)
		HWREGBITW(&gFlags, FRAME_BUFFER_READY) = 0;
	}
}

