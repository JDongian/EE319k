#include "DAC.h"
#include <lm3s1968.h>

void DAC_Init(void){int timingop;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
	timingop = 0;
	timingop = 1;
	GPIO_PORTF_DIR_R |= 0x0F;
	GPIO_PORTF_AFSEL_R |= 0x00;
	GPIO_PORTF_DEN_R |= 0x0F;
}
void DAC_Out(char bitsOut){
	GPIO_PORTF_DATA_R = bitsOut;
}
	





