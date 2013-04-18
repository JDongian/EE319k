// Use the SysTick timer to request interrupts at a particular period.

#include "lm3s1968.h"
#include "hw_types.h"
#include "ADC.h"
#include "Delay.h"

// **************SysTick_Init*********************
// Initialize Systick periodic interrupts
// Input: interrupt period
//        Units of period are 20ns
//        Maximum is 2^24-1
//        Minimum is determined by length of ISR
// Output: none
void SysTick_IntEnable(void);
void SysTick_Init(unsigned long);
void SysTick_Handler(void);

