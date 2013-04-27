#include "Main.h"

unsigned long gFlags;

int main(void){
	int i = 0; int t = 8; int dt = 2;
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
			t = t+dt;
			if(t > 600 || t < 10) dt *= -1;
			clearBuffer();
		//	drawRect(makePoint(1, 1), makePoint(127-1, 95-1), 0x2);
		//	drawRect(makePoint(0, 0), makePoint(127, 95), 0x1);
			
//			drawLine(makePoint(radius, radius), makePoint(127-radius, 95-radius), 0x2);
//			drawCircle(makePoint(128/2, 96/2), t, 0x1);
//			drawCircle(makePoint(128/2, 96/2), t+2, 0x2);

			drawRock(makePoint((t+5)/3, -1*t+5), 1, 1);
			drawRock(makePoint(2*t-75, (t+15)/2), 2, 3);			
			drawRock(makePoint(t+5, t-25), 3, 2);
			drawRock(makePoint(t-25, t+5), 4, 1);
			drawRock(makePoint(-1*t+60, -1*t+65), 5, 3);
			drawPlayer(makePoint(128/2+t-t*t/5000, 96/2-(t*t)/10000), i++);
			i %= 360;
			i += 1;
			HWREGBITW(&gFlags, FRAME_BUFFER_READY) = 1;
		}
	}
}

