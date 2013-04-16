#include "Main.h"
#define N 256 

unsigned long Data; // 10-bit ADC 
char* Position; // 16-bit fixed-point 0.001 cm 

int maint(void){
	int Data;
	//init();
	ADC_InitSWTriggerSeq3(2);
	SysTick_Init(20000000);
	while(1) {
		Data = ADC_In();
	}
}

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

int main3(void){ int i; unsigned long sum; 
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
		Position = convert(Data); // you write this function 
		LCD_GoTo(0); 
		LCD_OutString(Position);
	}
}
	
int main(void){
	PLL_Init();
	LCD_Open();
	LCD_Clear();
	ADC_InitSWTriggerSeq3(2);
	SysTick_Init(20000000);
	while(1){
		while(ADCStatus==0){}
		ADCStatus = 0;
		LCD_GoTo(0);
		LCD_OutString(convert(ADCMail));
		LCD_OutString(" cm");
	}
}


/*void init(void){
	int nop = 0;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOG;
	nop++;
	nop++;
	GPIOPinTypeGPIOInput(GPIO_PORTG_BASE,
											(GPIO_PIN_3 |
											 GPIO_PIN_4 |
	                     GPIO_PIN_5 |
	                     GPIO_PIN_6 |
	                     GPIO_PIN_7));
	GPIOPinTypeGPIOOutput(GPIO_PORTG_BASE, GPIO_PIN_2);
	GPIOPadConfigSet(GPIO_PORTG_BASE,
									(GPIO_PIN_3 |
	                 GPIO_PIN_4 |
	                 GPIO_PIN_5 |
	                 GPIO_PIN_6 |
	                 GPIO_PIN_7),
									 GPIO_STRENGTH_2MA,
					         GPIO_PIN_TYPE_STD_WPU);
}*/

char* convert(int input)
{
	char* output;
	output = " ";
	
	output[0] = 49;output[1] = 56;
	input -= MIN;
	input = input*(LENGTH/(MAX-MIN));
  output[0] = input/1000+48;
  output[1] = 46;
  output[2] = input%1000/100+48;
  output[3] = input%100/10+48;
  output[4] = input%10+48;
	return output;
}
