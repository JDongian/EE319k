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

void gameUpdate(void) {
	int i;
	gPlayer.x += gPlayer.dx;
	gPlayer.y += gPlayer.dy;
	gPlayer.dx = (gPlayer.dx*SPEED_DECAY);
	gPlayer.dy = (gPlayer.dy*SPEED_DECAY);
	switch(gPlayer.status) {
		point vertex, port, starboard, exhaust;
		point myShip[4];
		case ALIVE:
			//Button movement input
			if ((GPIO_PORTG_DATA_R&0xF8) == 0xF0) { //Up
				/*if ((g_soundArray == 0) || (g_soundIndex > SND_MOVE_LENGTH/2)) {
					g_soundArray = &g_soundMove;
					g_soundIndex = 0;
					g_soundMax = SND_MOVE_LENGTH; 
				}*/
				gPlayer.dx += cosDeg(gPlayer.angle)*PLAYER_ACCEL;
				gPlayer.dy -= sinDeg(gPlayer.angle)*PLAYER_ACCEL;
			}
			if ((GPIO_PORTG_DATA_R&0x20) == 0) { //Left
				gPlayer.angle += PLAYER_TURN_RATE;
			}
			if ((GPIO_PORTG_DATA_R&0x40) == 0) { //Right
				gPlayer.angle -= PLAYER_TURN_RATE;
			}
			if(gPlayer.dx < -4) { gPlayer.dx = -4; }
			if(gPlayer.dx > 4) { gPlayer.dx = 4; }
			if(gPlayer.dy < -4) { gPlayer.dy = -4; }
			if(gPlayer.dy > 4) { gPlayer.dy = 4; }
			
			if (HWREGBITW(&gFlags, FLAG_SELECT_BUTTON)) { //Shoot
				for (i = 0; i < MAX_PLAYER_BULLETS; i++) {
					if (gPlayerBullets[i].status == DEAD) {
						gPlayerBullets[i].status = ALIVE;
						gPlayerBullets[i].pos = makePoint((int)gPlayer.x, (int)gPlayer.y);
						gPlayerBullets[i].dx = (int)(sinDeg(gPlayer.angle)*BULLET_SPEED);
						gPlayerBullets[i].dy = (int)(cosDeg(gPlayer.angle)*BULLET_SPEED);
//						g_soundArray = &g_soundBullet;
//						g_soundIndex = 0;
//						g_soundMax = SND_BULLET_LENGTH; 
						break;
					}
				}
			}
			/*
			vertex = rotPoint(makePoint(gPlayer.x, gPlayer.y), angle, makePoint(loc.x+6, loc.y));
			port = rotPoint(loc, angle, makePoint(loc.x-5, loc.y-5));
			starboard = rotPoint(loc, angle, makePoint(loc.x-5, loc.y+5));
			exhaust = rotPoint(loc, angle, makePoint(loc.x-3, loc.y));
			myShip[0] = vertex;
			myShip[1] = port;
			myShip[2] = exhaust;
			myShip[3] = starboard;
			for(i = 0; i < 4; i++){
				if(myShip[i]) {
					gPlayer.status = HIT;
				}
			}*/	
			break;
		case HIT:
			break;
		case DEAD:
			break;
	}
	HWREGBITW(&gFlags, FLAG_SELECT_BUTTON) = 0;
}

void gameSet(short level) { //Gets the game ready for a new level.
	int i;
	centerPlayer();
	killBullets();
	killEnemies();
	if(level < 5) {
//		gRocks[
//				drawRock(makePoint((t+5)/3, -1*t+5), 1, 1);
//			drawRock(makePoint(2*t-75, (t+15)/2), 2, 3);			
//			drawRock(makePoint(t+5, t-25), 3, 2);
//			drawRock(makePoint(t-25, t+5), 4, 1);
//			drawRock(makePoint(-1*t+60, -1*t+65), 5, 3);
	}
}
void gameInit(void) {
	int i = 0;
	centerPlayer();
	killRocks();
	killBullets();
	killEnemies();
}
void addRock(point rockPos, int dx, int dy, unsigned char rockSize) {
	int i;
	for(i = 0; i < MAX_ROCKS; i++) {
		if(gRocks[i].status == ALIVE) {
		   
		}
	}
}
void centerPlayer()	{
	//Set the player in the center.
	gPlayer.x = 128/2;
	gPlayer.y = 96/2;
	gPlayer.dx = 0;
	gPlayer.dy = 0;
	gPlayer.angle = 90;
	gPlayer.status = ALIVE;
	gPlayer.step = 0;
}
void killRocks(void) {
	int i;
	//Set all rocks to dead.
	for(i = 0; i < MAX_ROCKS; i++) {
		gRocks[i].pos = makePoint(randRange(-20, 20), randRange(-20, 20));
		gRocks[i].dx = randRange(-2, 2);
		gRocks[i].dy = randRange(abs(gRocks[i].dx)-2, 2-abs(gRocks[i].dx));
		gRocks[i].status = DEAD;
		gRocks[i].rockType = randRange(0, 0xF);
		gRocks[i].rockSize = randRange(1,3);
	}
}
void killBullets(void) {
	int i;
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
}
void killEnemies(void) {
	int i;
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


