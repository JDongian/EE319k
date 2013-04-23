#include "Main.h"

int main(void){
	PLL_Init();
	SysTick_Init(2000000);
	Output_Init();
	Output_Color(15);
	SysTick_IntEnable();
	while(1) {
		//mainLoop
	}
}

