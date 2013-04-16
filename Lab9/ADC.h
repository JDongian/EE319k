#ifndef __ADCDRIVER_H__
#define __ADCDRIVER_H__

extern volatile unsigned long ADCvalue;

extern void ADC_Init(void);
extern unsigned long ADC_In(void);
void Timer0A_Handler(void);
void ADC_InitSWTriggerSeq3(unsigned char channelNum);

#endif // __ADCDRIVER_H__
#define ADCStatus								(*((volatile unsigned long *)0x00000000))
#define ADCMail									(*((volatile unsigned long *)0x00000000))
