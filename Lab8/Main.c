#include "Main.h"

int main(void){
	init();
	ADC_InitSWTriggerSeq3(2);
	SysTickInit();
	while(1) {
		Data = ADC_In();
	}
}

void init(void){
	int nop = 0;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOG;
	nop++;
	nop++;
	GPIOPinTypeGPIOInput(GPIO_PORTG_BASE,
											(GPIO_PIN_3 |
											 GPIO_PIN_4 |
	                     GPIO_PIN_5 |
	                     GPIO_PIN_6 |
	                     GPIO_PIN_7));
	GPIOPinTypeGPIOOutput(GPIO_PORTG_BASE, GPIO_PIN_2);
	GPIOPadConfigSet(GPIO_PORTG_BASE,
									(GPIO_PIN_3 |
	                 GPIO_PIN_4 |
	                 GPIO_PIN_5 |
	                 GPIO_PIN_6 |
	                 GPIO_PIN_7),
									 GPIO_STRENGTH_2MA,
					         GPIO_PIN_TYPE_STD_WPU);
}
