#include "globals.h"
#include "lm3s1968.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "LCD.h"
#include "SysTick.h"
#include "SysTickInts.h"
#include "rit128x96x4.h"
#include "PLL.h" 
#include "UART.h"
#include "FIFO.h"
#include "ADC.h"

#define MAX 1020
#define MIN 80
#define LENGTH 2000
#define N 1024

void SysTickIntHandler(void);
char convert(unsigned int);
