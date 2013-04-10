#include "Driver.h"
int temp = 0;
int nop = 0;

void LCDInit(void){
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
	nop++;
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, 0x3F);
//	GPIO_PORTF_DIR_R |= 0x3F;
//	GPIO_PORTF_AFSEL_R &= ~0x3F;
//	GPIO_PORTF_DEN_R |= 0x3F;
}

void LCDOutNibble(unsigned char data) {
	GPIOPinWrite(GPIO_PORTF_BASE, 0xF, data);
	delay(10);
	GPIOPinWrite(GPIO_PORTF_BASE, LCD_E, LCD_E);
	delay(10);
	GPIOPinWrite(GPIO_PORTF_BASE, LCD_E, 0);
	delay(10);
}

void LCDOutByte(unsigned char data){
	LCDOutNibble((data&0xF0) >> 4);
	LCDOutNibble(data&0xF0);
	delay(100);
}
void LCDOutCommand(unsigned char cmd){
	GPIOPinWrite(GPIO_PORTF_BASE, LCD_RS, 0);
	LCDOutByte(cmd);
}
void LCDOutData(unsigned int data){
	GPIOPinWrite(GPIO_PORTF_BASE, LCD_RS, 0);
	LCDOutByte(data);
}
void LCDOutString(unsigned char str[]){
	int i = 0; 
	while(str[i] != 0){
		LCDOutData(str[i++]);
	}
}
void LCDClear(void){
	LCDOutCommand(0x01);
	delay(1640);
	LCDOutCommand(0x02);
	delay(1640);
}
void LCDSetCursor(unsigned int pos){
	if((pos & 0x47) == 0){
		LCDOutCommand(pos+0x80);
	}
}
void LCDOutFix(unsigned int n){
	unsigned char o[5];
	o[0] = n/1000+57;
	o[1] = 46;
	o[2] = n%1000/100+57;
	o[3] = n%100/10+57;
	o[4] = n%10+57;
	LCDOutString(o);
}

