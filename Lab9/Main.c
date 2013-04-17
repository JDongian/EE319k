#include "Main.h"
 

unsigned long Data; // 10-bit ADC 
char* Position; // 16-bit fixed-point 0.001 cm 
//char output[6] = "      ";

void maint(void){
	PLL_Init(); // Bus clock is 50 MHz 
	LCD_Open(); 
	LCD_Clear();
	ADC_InitSWTriggerSeq3(2); // turn on ADC, set channel to 2, sequencer 3 
	UART_Init();
	UART_Enable();
	SysTick_Init(20000000);
	while(1){ }
}

char* convert(unsigned int input)
{
	char* output;
	
	if(input < MIN){
		input = 0;
	}	else {
		input -= MIN;
	}
	input = (input*(LENGTH))/(MAX-MIN);
  
	*output = input/1000+48;
  *(output+1) = '.';
  *(output+2) = (input%1000)/100+48;
  *(output+3) = (input%100)/10+48;
  *(output+4) = (input%10)+48;
	*(output+5) = 0;

	return output;
}

void main(void){
	int i; char flag;char* temp;
	char* storage = "                ";
	flag = 0;
	
	PLL_Init();
	UART_Init();
	LCD_Open();
	LCD_Clear();
	RxFifo_Init();
	
	while(1){
		while((RxFifo_Get(temp))==0){}
		if(temp == "2"){
			flag = 1;
		}
		if(flag){
			storage[i++] = temp[0];
		}
		if(temp == "3")
		{
			LCD_GoTo(0);
			LCD_OutString(storage);
			LCD_OutString("cm");
			flag = 0;
		}
	}
}

