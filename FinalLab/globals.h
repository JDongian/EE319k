#ifndef __GLOBALS_H__
#define __GLOBALS_H__
#define CLOCK_RATE              1000000

extern unsigned long gSystemClock;

extern unsigned long gFlags;
#define FRAME_BUFFER_READY			0				//If 1, the frame buffer is ready to be output to the screen.
#define FLAG_SELECT_BUTTON			1				//Is pressed

#include "lm3s1968.h"
#endif // __GLOBALS_H__
