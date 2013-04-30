#include <stdio.h>
#include "globals.h"
#include "lm3s1968.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "SysTick.h"
#include "SysTickInts.h"
#include "Timer.h"
#include "Sound.h"
#include "rit128x96x4.h"
#include "Output.h"
#include "PLL.h"
#include "DAC.h"

#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "DrawLib\draw2D.h"
#include "Game.h"

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

//void SysTickIntHandler(void);

