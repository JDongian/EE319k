#include "Main.h"
 

unsigned long Data; // 10-bit ADC 
char* Position; // 16-bit fixed-point 0.001 cm 
//char output[5] = "     ";

int main2(void){ int i; unsigned long sum; 
	PLL_Init(); // Bus clock is 50 MHz 
	LCD_Open(); 
	LCD_Clear(); 
	ADC_InitSWTriggerSeq3(2); // turn on ADC, set channel to 2, sequencer 3 
	while(1){ 
		sum = 0; 
		for(i=0; i<N; i++){ // take N samples and perform the average 
			sum = sum+ADC_In(); // sample 10-bit channel 2 
		} 
		Data = sum/N; // noise reducing filter 
		LCD_GoTo(0);  
		LCD_OutDec(Data); LCD_OutString(" "); 
	} 
}

int main(void){ int i; unsigned long sum; 
	PLL_Init(); // Bus clock is 50 MHz 
	LCD_Open(); 
	LCD_Clear(); 
	ADC_InitSWTriggerSeq3(2); // turn on ADC, set channel to 2, sequencer 3 
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

char* convert(unsigned int input)
{
	char* output;
	if(input < MIN)
	{
		input = 0;
	}
	else
	{
		input -= MIN;
	}
	input = (input*(LENGTH))/(MAX-MIN);
  *output = input/1000+48;
	*(output+1) = '.';
	*(output+2) = (input%1000)/100+48;
	*(output+3) = (input%10)+48;
	*(output+4) = 0;
	return output;
}
