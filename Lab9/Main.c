#include "Main.h"


unsigned long Data; // 10-bit ADC 
char* Position; // 16-bit fixed-point 0.001 cm 
//char output[6] = "      ";
char output[6] = "      ";

int maint(void){
	PLL_Init();
	UART_Init();
	RxFifo_Init();
	UART_Enable();
	ADC_InitSWTriggerSeq3(2); // turn on ADC, set channel to 2, sequencer 3 
	SysTick_Init(20000000);
	SysTick_IntEnable();
	while(1){ }
}

int main(void){
	int i = 0; char flag = 0;char temp = ' ';
	char storage[6] = "      ";
	
	PLL_Init();
	SysTick_Init(2000000);
	Output_Init();
	Output_Color(15);
	UART_Init();
	ADC_InitSWTriggerSeq3(2);
	LCD_Open();
	LCD_Clear();
	RxFifo_Init();
	UART_Enable();
	SysTick_IntEnable();
	EnableInterrupts();
	while(1) {
		while((RxFifo_Get(&temp))==0){}
		if(temp == 3) {
			LCD_GoTo(0);
			LCD_OutChar(storage[0]);
			LCD_OutChar(storage[1]);
			LCD_OutChar(storage[2]);
			LCD_OutChar(storage[3]);
			LCD_OutChar(storage[4]);
			LCD_OutChar(' ');
			LCD_OutString("cm");
			flag = 0;
			i = 0;
		}
		if(flag) {
			storage[i++] = temp;
		}
		if(temp == 2) {
			flag = 1;
		}
	}
}

char* convert(unsigned int input){
	if(input < MIN){
		input = 0;
	}	else {
		input -= MIN;
	}
	input = (input*(LENGTH))/(MAX-MIN);
  
	output[0] = input/1000+48;
  output[1] = '.';
  output[2] = (input%1000)/100+48;
  output[3] = (input%100)/10+48;
  output[4] = (input%10)+48;

	return output;
}

