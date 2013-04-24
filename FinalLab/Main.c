#include "Main.h"

unsigned long gFlags;

int main(void){
	PLL_Init();
	SysTick_Init(2000000);
	Output_Init();
	Output_Color(15);
	SysTick_IntEnable();
	while(1) {
		if(HWREGBITW(&gFlags, FRAME_BUFFER_READY) == 0) { continue; }
		clearBuffer();
		demo();
		HWREGBITW(&gFlags, FRAME_BUFFER_READY) = 1;
	}
}

