#include "Piano.h"
#include "Sound.h"
#include <lm3s1968.h>

void Piano_Init(void){
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOG;
	GPIO_PORTG_DIR_R &= ~0x19;
	GPIO_PORTG_AFSEL_R &= ~0x19;
	GPIO_PORTG_DEN_R |= 0x19;
}

int Piano_In(void){
	return A4;
	if((GPIO_PORTG_DATA_R & 0x05) == 0x05) //LEFT BUTTON
	{
		//PLAY SOUND FOR LEFT BUTTON
		return C4;
	}
	else if((GPIO_PORTG_DATA_R & 0x03) == 0x03) //UP BUTTON
	{
		//PLAY SOUND FOR UP BUTTON
		return D4;
	}
	else if((GPIO_PORTG_DATA_R & 0x06) == 0x06) //RIGHT BUTTON
	{
		//PLAY SOUND FOR RIGHT BUTTON
		return E4;
	}
	else if((GPIO_PORTG_DATA_R & 0x04) == 0x04) //DOWN BUTTON
	{
		//PLAY SOUND FOR DOWN	BUTTON
		return F4;
	}
	else if((GPIO_PORTG_DATA_R & 0x07) == 0x07) //SELECT BUTTON
	{
		//PLAY SOUND FOR SELECT BUTTON
		return G4;
	}
	return A4;
}



