#include "Game.h"

unsigned char bulletSprite[3][3] = {
	{0x00, 0x04, 0x00},
	{0x04, 0x0C, 0x04},
	{0x00, 0x04, 0x00}
};

playerState gPlayer;
rockState gRocks[MAX_ROCKS];
bulletState gPlayerBullets[MAX_PLAYER_BULLETS];
bulletState gEnemyBullets[MAX_ENEMY_BULLETS];
agentState gUFOs[MAX_UFOS];
agentState gSatellites[MAX_SATELLITES*3];

void gameInit(void) {
	int i = 0;
	//Set the player in the center.
	gPlayer.x = 128/2;
	gPlayer.y = 96/2;
	gPlayer.dx = 0;
	gPlayer.dy = 0;
	gPlayer.angle = 90;
	gPlayer.status = ALIVE;
	gPlayer.step = 0;
	
	//Set all bullets to dead.
	for(i = 0; i < MAX_PLAYER_BULLETS; i++) {
		gPlayerBullets[i].pos = makePoint(0,0);
		gPlayerBullets[i].dx = 0;
		gPlayerBullets[i].dy = 0;
		gPlayerBullets[i].status = DEAD;
	}
	for(i = 0; i < MAX_ENEMY_BULLETS; i++) {
		gEnemyBullets[i].pos = makePoint(0,0);
		gEnemyBullets[i].dx = 0;
		gEnemyBullets[i].dy = 0;
		gEnemyBullets[i].status = DEAD;
	}
	//Set all rocks to dead.
	for(i = 0; i < MAX_ROCKS; i++) {
		gRocks[i].pos = makePoint(randRange(-20, 20), randRange(-20, 20));
		gRocks[i].dx = randRange(-2, 2);
		gRocks[i].dy = randRange(abs(gRocks[i].dx)-2, 2-abs(gRocks[i].dx));
		gRocks[i].status = DEAD;
		gRocks[i].rockType = randRange(0, 0xF);
		gRocks[i].rockSize = randRange(1,3);
	}
	//Set all UFOs to dead.
	for(i = 0; i < MAX_UFOS; i++) {
		gUFOs[i].pos = makePoint(0,0);
		gUFOs[i].dx = 0;
		gUFOs[i].dy = 0;
		gUFOs[i].status = DEAD;
		gUFOs[i].type = UFO_LARGE;
	}
	//Set all Satellites to dead.
	for(i = 0; i < MAX_SATELLITES*3; i++) {
		gSatellites[i].pos = makePoint(0,0);
		gSatellites[i].dx = 0;
		gSatellites[i].dy = 0;
		gSatellites[i].status = DEAD;
		gSatellites[i].type = SATELLITE;
	}
}

