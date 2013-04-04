#include "Piano.h"
#include "Sound.h"
#include <lm3s1968.h>

void Piano_Init(void){ 
}

//LEFT 0b11011000		RIGHT 0b10111000		UP	0b11110000		DOWN	0b11101000			SELECT 0b01110000
int Piano_In(void){
	unsigned long key = GPIO_PORTG_DATA_R;
	if((key & 0x20) == 0) //LEFT BUTTON
	{
		//PLAY SOUND FOR LEFT BUTTON
		return C4;
	}
	else if((key & 0x08) == 0) //UP BUTTON
	{
		//PLAY SOUND FOR UP BUTTON
		return D4;
	}
	else if((key & 0x40) == 0) //RIGHT BUTTON
	{
		//PLAY SOUND FOR RIGHT BUTTON
		return E4;
	}
	else if((key & 0x10) == 0) //DOWN BUTTON
	{
		//PLAY SOUND FOR DOWN	BUTTON
		return F4;
	}
	else if((key & 0x80) == 0) //SELECT BUTTON
	{
		//PLAY SOUND FOR SELECT BUTTON
		return G4;
	}
	return Off;
}



