#include "Piano.h"
#include <lm3s1968.h>

void Piano_Init(void){
	
	GPIO_PORTG_DIR_R &= ~0x19;
	GPIO_PORTG_AFSEL_R &= ~0x19;
	GPIO_PORTG_DEN_R |= 0x19;
}

key Piano_In(void){
	
	
	if((GPIO_PORTG_DATA_R & 0x05) == 0x05) //LEFT BUTTON
	{
		//PLAY SOUND FOR LEFT BUTTON
	}
	else if((GPIO_PORTG_DATA_R & 0x03) == 0x03) //UP BUTTON
	{
		//PLAY SOUND FOR UP BUTTON
	}
	else if((GPIO_PORTG_DATA_R & 0x06) == 0x06) //RIGHT BUTTON
	{
		//PLAY SOUND FOR RIGHT BUTTON
	}
	if((GPIO_PORTG_DATA_R & 0x04) == 0x04) //DOWN BUTTON
	{
		//PLAY SOUND FOR DOWN	BUTTON
	}
	if((GPIO_PORTG_DATA_R & 0x07) == 0x07) //SELECT BUTTON
	{
		//PLAY SOUND FOR SELECT BUTTON
	}
	return 0;
}



