#include "Main.h"

unsigned long gFlags;
short gameLevel;

int main(void){
	int i = 0;
	bool isLevelComplete;
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
//dont work right...	setSeed(11);
	setGraphics(0);//the lm3s can't handle more than 2 rocks at graphics level 3.
	gameInit();
	gameSet(1);
	while(1) {
		if(HWREGBITW(&gFlags, FRAME_BUFFER_READY) == 0) {
			//Check for level completion, aka all rocks and enemies are 
			//TODO: enemies
			for(i = 0; i < MAX_ROCKS; i++) {
				if(gRocks[i].status == ALIVE) {
					isLevelComplete = False;
					break;
				}
			} if(i == MAX_ROCKS) {isLevelComplete = True; }
			if(isLevelComplete) { gameSet(++gameLevel); }
			clearBuffer();
			//Draw the player.
			gameUpdate();
			drawPlayer(makePoint((int)gPlayer.x, (int)gPlayer.y), gPlayer.angle);
			for(i = 0; i < MAX_ROCKS; i++) {
				if(gRocks[i].status == ALIVE) {
					drawRock(gRocks[i].pos, gRocks[i].rockType, gRocks[i].rockSize);
				}
			}
			for(i = 0; i < MAX_PLAYER_BULLETS; i++) {}
			for(i = 0; i < MAX_ENEMY_BULLETS; i++) {}
			HWREGBITW(&gFlags, FRAME_BUFFER_READY) = 1;
		}
	}
}

