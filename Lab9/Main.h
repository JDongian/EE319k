#include "globals.h"
#include "lm3s1968.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include <stdio.h>

#include "Output.h"
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

// standard ASCII symbols
#define BACKSPACE               0x8  // back up one character
#define TAB                     0x9  // move cursor right
#define HOME                    0xA  // move cursor all the way left on current line
#define NEWLINE                 0xD  // move cursor all the way left on next line
#define RETURN                  0xD  // move cursor all the way left on next line
#define CR   0x0D
#define LF   0x0A
#define BS   0x08
#define ESC  0x1B
#define SP   0x20
#define DEL  0x7F

void EnableInterrupts(void);

void SysTickIntHandler(void);
char* convert(unsigned int);
