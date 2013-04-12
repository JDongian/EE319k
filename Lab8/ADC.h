#ifndef __ADCDRIVER_H__
#define __ADCDRIVER_H__

extern volatile unsigned long ADCvalue;

extern void ADC_Init(void);
extern unsigned long ADC_In(void);
void Timer0A_Handler(void);

#endif // __ADCDRIVER_H__
