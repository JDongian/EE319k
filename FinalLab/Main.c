#include "Main.h"

unsigned long gFlags;

int main(void){
	int i = 0; int radius = 8;
	PLL_Init();
//	ADC_Init(2);
	Sound_Init();
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
												GPIOPinTypeGPIOInput(GPIO_PORTG_BASE,
												(GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7));
												GPIOPinTypeGPIOOutput(GPIO_PORTG_BASE, GPIO_PIN_2);
												GPIOPadConfigSet(GPIO_PORTG_BASE,
												(GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7),
												GPIO_STRENGTH_2MA,
												GPIO_PIN_TYPE_STD_WPU);
	
	SysTick_Init(2000000);
	Output_Init();
	Output_Color(15);
	SysTick_IntEnable();
	gFlags = 0;
	setGraphics(0);
	while(1) {
		if(HWREGBITW(&gFlags, FRAME_BUFFER_READY) == 0) {
			radius = (radius+2);
			clearBuffer();
		//	drawRect(makePoint(1, 1), makePoint(127-1, 95-1), 0x2);
		//	drawRect(makePoint(0, 0), makePoint(127, 95), 0x1);
			
			drawLine(makePoint(radius, radius), makePoint(127-radius, 95-radius), 0x2);
//			drawCircle(makePoint(128/2, 96/2), radius, 0x2);
//			drawCircle(makePoint(128/2, 96/2), radius+2, 0x4);
			drawPlayer(makePoint(128/2, 96/2), i++);
			i %= 360;
			i += 9;
			HWREGBITW(&gFlags, FRAME_BUFFER_READY) = 1;
		}
	}
}

