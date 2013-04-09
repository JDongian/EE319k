#include "lm3s1968.h"
#include "Driver.h"
	int nop = 0;
	int temp = 0;

void LCDInit(void){
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
	nop++;
	nop=nop*2;
	GPIO_PORTF_DIR_R |= 0x3F;
	GPIO_PORTF_AFSEL_R &= ~0x3F;
	GPIO_PORTF_DEN_R |= 0x3F;

}
void LCDOutNibble(unsigned char data){
	GPIO_LCD_CTRL_F = data;
	Delay(125);
	GPIO_LCD_E = 0xFF;
	Delay(70);
	GPIO_LCD_E = 0;
	Delay(90);

}
void LCDOutByte(unsigned char data){
		GPIO_LCD_RS = 0x20;
	temp = data;
	data = data >> 4;
	LCDOutNibble(data);
	data = temp;
	data &= ~0xF0;
	LCDOutNibble(data);

}
void LCDOutCommand(unsigned char cmd){
	GPIO_LCD_RS = 0;
	temp = cmd;
	cmd = cmd >> 4;
	LCDOutNibble(cmd);
	cmd = temp;
	cmd &= ~0xF0;
	LCDOutNibble(cmd);

}
void LCDOutData(unsigned int data){

	
}
void LCDOutString(unsigned char str[]){
	int i = 0;
	while(str[i] != 0)
	{
		LCDOutData(str[i]);
		i++;
	}
	
	

}
void LCDClear(void){
	GPIO_LCD_RS = 0;
	LCDOutCommand(1);
	Delay(1640);
	LCDOutCommand(2);
	Delay(1640);
	

}
void LCDSetCursor(unsigned int pos){
	
	GPIO_LCD_RS = 0;
	pos &= 0x47;
	if(pos == 0)
	{return;}
	pos += 0x80;
	LCDOutCommand(pos);

}
void LCDOutFix(unsigned int num){
}
