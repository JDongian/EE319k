#include "globals.h"
#include "SysTick.h"
#include "lm3s1968.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "PLL.h" 
#include "ADC.h"
#include "LCD.h"
#include "SysTickInts.h"

#define MAX 1020
#define MIN 80
#define LENGTH 2000

void SysTickIntHandler(void);
void init(void);
unsigned char* convert(int input);
