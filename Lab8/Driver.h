


void LCDInit(void);
void LCDOutNibble(unsigned char);
void LCDOutByte(unsigned char);
void LCDOutCommand(unsigned char);
void LCDOutData(unsigned int);
void LCDOutString(unsigned char []);
void LCDClear(void);
void LCDSetCursor(unsigned int);
void LCDOutFix(unsigned int);