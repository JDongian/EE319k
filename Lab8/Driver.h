#include "lm3s1968.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/lm3s1968.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "Delay.h"

//LCD pins
#define LCD_RS	0x20
#define LCD_E		0x10

void LCDInit(void);
void LCDOutNibble(unsigned char);
void LCDOutByte(unsigned char);
void LCDOutCommand(unsigned char);
void LCDOutData(unsigned int);
void LCDOutString(unsigned char []);
void LCDClear(void);
void LCDSetCursor(unsigned int);
void LCDOutFix(unsigned int);


