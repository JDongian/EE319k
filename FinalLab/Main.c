#include "Main.h"

unsigned long gFlags;

int main(void){
	int i = 0;
	PLL_Init();
	SysTick_Init(2000);
	Output_Init();
	Output_Color(15);
	SysTick_IntEnable();
	gFlags = 0;
	while(1) {
		if(HWREGBITW(&gFlags, FRAME_BUFFER_READY) == 0) {
			clearBuffer();		
			demo();
			drawPlayer(makePoint(128/2, 96/2), i);
			i += 10;
			i %= 360;
			HWREGBITW(&gFlags, FRAME_BUFFER_READY) = 1;
		}
	}
}

