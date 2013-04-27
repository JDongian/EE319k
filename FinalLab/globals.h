#ifndef __GLOBALS_H__
#define __GLOBALS_H__
#define CLOCK_RATE              1000000

extern unsigned long gSystemClock;

extern unsigned long gFlags;
#define FRAME_BUFFER_READY			0				//If 1, the frame buffer is ready to be output to the screen.

extern unsigned char gGraphicsSetting;
//0 = line
//1 = shaded
//2 = best shaded

extern unsigned char* frameBuffer[64*96];

#endif // __GLOBALS_H__
