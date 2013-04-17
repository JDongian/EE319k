#include "Main.h"
 

unsigned long Data; // 10-bit ADC 
char* Position; // 16-bit fixed-point 0.001 cm 
char output[6] = "      ";

int main(void){ int i; unsigned long sum;
	PLL_Init(); // Bus clock is 50 MHz 
	LCD_Open(); 
	LCD_Clear();
	ADC_InitSWTriggerSeq3(2); // turn on ADC, set channel to 2, sequencer 3 
	UART_Init();
	UART_Enable();
	SysTick_Init(20000000);
	while(1){ 
		sum = 0; 
		for(i=0; i<N; i++){ // take N samples and perform the average 
			sum += ADC_In(); // sample 10-bit channel 2 
		} 
		Data = sum/N; // noise reducing filter 
		Position = convert(Data);
		LCD_GoTo(0); 
		LCD_OutString(Position);
	}
}

char convert(unsigned int input)
{
	if(input < MIN)
	{
		input = 0;
	}
	else
	{
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
/*
int mainTr(void){int i; char flag;char* temp;
	char* storage = "                ";
	flag = 0;
	
	PLL_Init();
	UART_Init();
	LCD_Open();
	LCD_Clear();
	RxFifo_Init();
	
	while(1){
		while((RxFifo_Get(temp))==0){}
			if(temp == "2")
			{
				flag = 1;
			}
		if(flag)
		{
			storage[i++] = temp[0];
		}
			if(temp == "3")
			{
				LCD_GoTo(0);
				LCD_OutString(storage);
				LCD_OutString("cm");
				flag = 0;
			}
			
		}}
*/

