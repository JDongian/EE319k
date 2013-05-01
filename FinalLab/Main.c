#include "Main.h"


unsigned long gFlags;
short gameLevel;
int score;

int main(void){
	int i = 0;
	//Score set
	score = 0;
	PLL_Init();
	//Sound init
	DAC_Init();
	Timer0A_Init(Sound_Update, 1000000/11025);
//	Timer0B_Init(updateXAxis, 1000000/11025);
//	Timer1B_Init(updateYAxis, 1000000/11025);
	//Input
	ADC_Init();
	portD_Init();
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
												GPIOPinTypeGPIOInput(GPIO_PORTG_BASE,
												(GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7));
												GPIOPinTypeGPIOOutput(GPIO_PORTG_BASE, GPIO_PIN_2);
												GPIOPadConfigSet(GPIO_PORTG_BASE,
												(GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7),
												GPIO_STRENGTH_2MA,
												GPIO_PIN_TYPE_STD_WPU);
	SysTick_Init(50000000/400);
	Output_Init();
	Output_Color(15);
	SysTick_IntEnable();
	updateXAxis();
	setXYAvg();
	EnableInterrupts();
	//Clear flags
	gFlags = 0;
	//Math rand set
	while ((GPIO_PORTG_DATA_R & 0x80) != 0) { }
	while ((GPIO_PORTG_DATA_R & 0x80) == 0) { }
	setSeed(NVIC_ST_CURRENT_R);
	//Game set
	setGraphics(0);//the lm3s can't handle more than 2 rocks at graphics level 3.
	gameInit();
	gameSet(1);
	setXYAvg();
	while(1) {
		//Only draw to buffer when it has been output to the screen
		if(HWREGBITW(&gFlags, FRAME_BUFFER_READY) == False) {
			//Check for level completion, aka all rocks and enemies are 
			//TODO: enemies
			if(HWREGBITW(&gFlags, LEVEL_COMPLETE) == True) { gameSet(++gameLevel); }
			//Redraw the screen from scratch.
			clearBuffer();
			//Draw the player.
			if(gPlayer.status == ALIVE) {
				drawPlayer(makePoint((int)gPlayer.x, (int)gPlayer.y),
									 gPlayer.angle, gPlayer.exhaustOn);
			}
			for(i = 0; i < MAX_ROCKS; i++) {
				if(gRocks[i].status == ALIVE) {
					drawRock(makePoint(gRocks[i].x, gRocks[i].y),
									 gRocks[i].rockType, gRocks[i].rockSize);
				}
			}
			//Draw allied bullets.
			for(i = 0; i < MAX_PLAYER_BULLETS; i++) {
				if(gPlayerBullets[i].status == ALIVE) {
					drawBullet(makePoint(gPlayerBullets[i].x, gPlayerBullets[i].y));
				}
			}
			//Draw enemy bullets.
			for(i = 0; i < MAX_ENEMY_BULLETS; i++) {
				if(gEnemyBullets[i].status == ALIVE) {
					drawBullet(makePoint(gEnemyBullets[i].x, gEnemyBullets[i].y));
				}
			}
			//Draw explosions.
			for(i = 0; i < MAX_EXPLOSIONS; i++) {
				if(gExplosions[i].status == ALIVE) {
					drawExplosion(gExplosions[i].pos, gExplosions[i].current);
				}
			}
			
			//
			//drawString(score, makePoint(0,0));
			gameUpdate();
			HWREGBITW(&gFlags, FRAME_BUFFER_READY) = True;
		}
	}
}
