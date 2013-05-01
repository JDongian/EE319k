#ifndef __ADCDRIVER_H__
#define __ADCDRIVER_H__

extern void ADC_Init(void);
extern unsigned long ADC_In(void);
void Timer0B_Handler(void);
void ADC_InitSWTriggerSeq3(unsigned char channelNum);
unsigned long getADC1Value(void);
void Timer1B_Init10HzInt(void);
extern volatile unsigned int ADCStatus;
extern volatile unsigned long ADCMail;

#endif // __ADCDRIVER_H__
