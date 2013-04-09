


extern void LCDInit(void);
extern void LCDOutNibble(unsigned char);
extern void LCDOutByte(unsigned char);
extern void LCDOutCommand(unsigned char);
extern void LCDOutData(unsigned int);
extern void LCDOutString(unsigned char []);
extern void LCDClear(void);
extern void LCDSetCursor(unsigned int);
extern void LCDOutFix(unsigned int);