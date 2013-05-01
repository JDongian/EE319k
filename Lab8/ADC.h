
extern void ADC_Init(void);
extern unsigned long ADC_In0(void);
extern unsigned long ADC_In1(void);
void Timer0B_Handler(void);
void Timer1B_Handler(void);
void ADC_InitSWTriggerSeq3(unsigned char channelNum);

extern volatile unsigned int ADCStatus0;
extern volatile unsigned long ADCMail0;
extern volatile unsigned int ADCStatus1;
extern volatile unsigned long ADCMail1;

