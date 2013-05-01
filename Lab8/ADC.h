#ifndef __ADCDRIVER_H__
#define __ADCDRIVER_H__

extern void ADC_Init(void);
extern unsigned long ADC_In(void);
void Timer0B_Handler(void);
void ADC_InitSWTriggerSeq3(unsigned char channelNum);

extern unsigned long getADC0Value(void);

extern volatile unsigned int ADCStatus;
extern volatile unsigned long ADCMail;

#endif // __ADCDRIVER_H__
