#ifndef __GLOBALS_H__
#define __GLOBALS_H__
#define CLOCK_RATE              1000000

#include "drawlib\draw2D.h"


extern unsigned long gSystemClock;

extern unsigned long gFlags;
#define FRAME_BUFFER_READY			0				//If 1, the frame buffer is ready to be output to the screen.
#define LEVEL_COMPLETE					1				//
#define SELECT_DOWN							2				//
#define ANALOG_LEFT							3				//
#define ANALOG_RIGHT						4				//
#define ANALOG_UP								5				//
#define ANALOG_DOWN							6				//
#define GAME_OVER								7				//Game is over?
#define TITLE_SCREEN						8				//ASTEROIDS
//#define ADC_X_READY							7				//
//#define ADC_X_READY							7				//



extern unsigned char gGraphicsSetting;

extern int score;

#include "lm3s1968.h"
#endif // __GLOBALS_H__
