#include "DAC.h"
#include <lm3s1968.h>

void DAC_Init(void){
	GPIO_PORTF_DIR_R |= 0x07;
	GPIO_PORTF_AFSEL_R &= ~0x07;
	GPIO_PORTF_DEN_R |= 0x07;
	//GPIO_PORTF_PUR_R |= 0x07;
	
}
void DAC_Out(char bitsOut){
	GPIO_PORTF_DATA_R = bitsOut;
}
	





