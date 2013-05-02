#ifndef __ADCDRIVER_H_
#define	ADC_SAMPLE_NUMBER		256
#define __ADCDRIVER_H__


extern void ADC_Init(void);
extern unsigned long ADC_In(void);
void Timer0B_Handler(void);
void ADC_InitSWTriggerSeq3(unsigned char channelNum);

extern volatile unsigned int ADCStatus0;
extern volatile unsigned int ADCStatus1;
extern volatile unsigned long ADCValue0;
extern volatile unsigned long ADCValue1;

#endif // __ADCDRIVER_H__
