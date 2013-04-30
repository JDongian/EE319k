#include "Game.h"

playerState gPlayer;
rockState gRocks[MAX_ROCKS];
bulletState gPlayerBullets[MAX_PLAYER_BULLETS];
bulletState gEnemyBullets[MAX_ENEMY_BULLETS];
agentState gUFOs[MAX_UFOS];
agentState gSatellites[MAX_SATELLITES*3];
explosionState gExplosions[MAX_EXPLOSIONS];
bool selectStatus = False;

void gameUpdate(void) {
	point vertex, port, starboard, exhaust, playerPos;
	point playerShip[5];
	int i, j;
	//Level defaults to finished, changed when rocks or enemies are alive.
	HWREGBITW(&gFlags, LEVEL_COMPLETE) = True;
	//Update player
	gPlayer.x += gPlayer.dx;
	gPlayer.y += gPlayer.dy;
	gPlayer.x = floatMod(gPlayer.x, 128);
	gPlayer.y = floatMod(gPlayer.y, 96);
	gPlayer.dx = (gPlayer.dx*SPEED_DECAY);
	gPlayer.dy = (gPlayer.dy*SPEED_DECAY);
	gPlayer.exhaustOn = False;
	playerPos = makePoint((int)gPlayer.x, (int)gPlayer.y);
	vertex = rotPoint(playerPos, gPlayer.angle,
										makePoint(playerPos.x+6, playerPos.y));
	port = rotPoint(playerPos, gPlayer.angle,
									makePoint(playerPos.x-5, playerPos.y-5));
	starboard = rotPoint(playerPos, gPlayer.angle,
											 makePoint(playerPos.x-5, playerPos.y+5));
	exhaust = rotPoint(playerPos, gPlayer.angle,
										 makePoint(playerPos.x-3, playerPos.y));
	playerShip[0] = vertex;
	playerShip[1] = port;
	playerShip[2] = exhaust;
	playerShip[3] = starboard;
	playerShip[4] = makePoint((int)gPlayer.x, (int)gPlayer.y);
	switch(gPlayer.status) {
		case ALIVE:
			////Button movement input
			//Forward (up)
			if ((GPIO_PORTG_DATA_R&0x08) == 0) {
				if((gPlayer.dx*gPlayer.dx + gPlayer.dy*gPlayer.dy) <
					 MAX_PLAYER_SPEED*MAX_PLAYER_SPEED) {
					gPlayer.dx += cosDeg(gPlayer.angle)*PLAYER_ACCEL;
					gPlayer.dy -= sinDeg(gPlayer.angle)*PLAYER_ACCEL;
				}
				gPlayer.exhaustOn = True;
			}
			//Left
			if ((GPIO_PORTG_DATA_R&0x20) == 0) { gPlayer.angle += PLAYER_TURN_RATE; }
			//Right
			if ((GPIO_PORTG_DATA_R&0x40) == 0) { gPlayer.angle -= PLAYER_TURN_RATE; }
			//Selecte
			if((GPIO_PORTG_DATA_R&0x80) != 0) {
				selectStatus = False;
			}
			//Positive edge
			if((selectStatus == False) && ((GPIO_PORTG_DATA_R&0x80) == 0)) {
				selectStatus = True;
				gSoundArray = &gSoundBullet;
				gSoundIndex = 0;
				gSoundMaxLength = SND_BULLET_LENGTH;
				addBullet(makePoint((int)gPlayer.x, (int)gPlayer.y),
									(cosDeg(gPlayer.angle)*MAX_BULLET_SPEED),
									-1*(sinDeg(gPlayer.angle)*MAX_BULLET_SPEED),
									True);
			}
			break;
		case HIT:
			addExplosion(makePoint(gPlayer.x, gPlayer.y), 4);
			gPlayer.dx = 0;
			gPlayer.dy = 0;
			gPlayer.status = DEAD;
			break;
		case DEAD:
			//Wait for explosions to stop, then stop updating the game.
			for(i = 0; i < MAX_EXPLOSIONS; i++) {
				if(gExplosions[i].status == ALIVE) { break; }
			}
			return;
	}
	//Update bullets
	for(i = 0; i < MAX_PLAYER_BULLETS; i++) {
		switch(gPlayerBullets[i].status) {		//Only update visible bullets.
			case ALIVE:
				if(gPlayerBullets[i].life++ > BULLET_LIFETICKS) {
					gPlayerBullets[i].status = DEAD;
					break;
				}
				gPlayerBullets[i].x = gPlayerBullets[i].x+gPlayerBullets[i].dx;
				gPlayerBullets[i].y = gPlayerBullets[i].y+gPlayerBullets[i].dy;
			case HIT:
				break;
			case DEAD:
				break;
		}
	}
	for(i = 0; i < MAX_ENEMY_BULLETS; i++) {
		switch(gEnemyBullets[i].status) {		//Only update visible bullets.
			case ALIVE:
				if(gEnemyBullets[i].life++ > BULLET_LIFETICKS) {
					gEnemyBullets[i].status = DEAD;
					break;
				}
				HWREGBITW(&gFlags, LEVEL_COMPLETE) = False;
				gEnemyBullets[i].x = gEnemyBullets[i].x+gEnemyBullets[i].dx;
				gEnemyBullets[i].y = gEnemyBullets[i].y+gEnemyBullets[i].dy;
			case HIT:
				break;
			case DEAD:
				break;
		}
	}
	//Update rocks
	for(i = 0; i < MAX_ROCKS; i++) {
		switch(gRocks[i].status) {
			case ALIVE:		//Only update visible rocks.
				HWREGBITW(&gFlags, LEVEL_COMPLETE) = False;
				//Update rock position
				if(gRocks[i].dx < 0.1 && gRocks[i].dy < 0.1) {
					gRocks[i].dx = (randRange(32,64)*-1+randRange(32,64)*1)/64.;
					gRocks[i].dy = randRange(0,256)/256;
				}
				gRocks[i].x = floatMod(gRocks[i].x+gRocks[i].dx, 128);
				gRocks[i].y = floatMod(gRocks[i].y+gRocks[i].dy, 96);
				//Check collisions with enemies, players and bullets.
				//Player collision
				for(j = 0; j < 5; j++) {
					if(pointInRock(makePoint(((int)gRocks[i].x),
																	 ((int)gRocks[i].y)),
												 gRocks[i].rockType,
												 gRocks[i].rockSize,
												 playerShip[j])) {
						gPlayer.status = HIT;
					}
				}
				//Bullet collision
				for(j = 0; j < MAX_PLAYER_BULLETS; j++) {
					if(gPlayerBullets[i].status == ALIVE) {
						if(pointInRock(makePoint(((int)gRocks[i].x),
																		 ((int)gRocks[i].y)),
													 gRocks[i].rockType,
													 gRocks[i].rockSize,
													 makePoint(((int)gPlayerBullets[j].x+1),
																		 ((int)gPlayerBullets[j].y+1))) ||
							 pointInRock(makePoint(((int)gRocks[i].x),
																		 ((int)gRocks[i].y)),
													 gRocks[i].rockType,
													 gRocks[i].rockSize,
													 makePoint(((int)gPlayerBullets[j].x+1),
																		 ((int)gPlayerBullets[j].y-1))) ||
							 pointInRock(makePoint(((int)gRocks[i].x),
																		 ((int)gRocks[i].y)),
													 gRocks[i].rockType,
													 gRocks[i].rockSize,
													 makePoint(((int)gPlayerBullets[j].x-1),
																		 ((int)gPlayerBullets[j].y+1))) ||
							 pointInRock(makePoint(((int)gRocks[i].x),
																		 ((int)gRocks[i].y)),
													 gRocks[i].rockType,
													 gRocks[i].rockSize,
													 makePoint(((int)gPlayerBullets[j].x-1),
																		 ((int)gPlayerBullets[j].y-1)))) {
							score += 2;
							addExplosion(makePoint(gPlayerBullets[j].x,
																		 gPlayerBullets[j].y), 1);
							gRocks[i].status = HIT;
							gPlayerBullets[j].status = DEAD;
						}
					}
				}
				for(j = 0; j < MAX_ENEMY_BULLETS; j++) {
					if(gEnemyBullets[i].status == ALIVE) {
						if(pointInRock(makePoint(((int)gRocks[i].x),
																		 ((int)gRocks[i].y)),
													 gRocks[i].rockType,
													 gRocks[i].rockSize,
													 makePoint(((int)gEnemyBullets[j].x)%128,
																		 ((int)gEnemyBullets[j].y)%96))) {
							gRocks[i].status = HIT;
							addExplosion(makePoint(gEnemyBullets[j].x,
																		 gEnemyBullets[j].y), 2);																	 
							gEnemyBullets[j].status = DEAD;
						}
					}
				}
				if(gRocks[i].status == ALIVE) { break; }
			case HIT:
				if(gRocks[i].rockSize > 1) {
					addRock(makePoint((int)gRocks[i].x+2, (int)gRocks[i].y+2),
									randRange(gRocks[i].dx*48+16,0)/64.,
									randRange(gRocks[i].dy*48+16,0)/64.,
									gRocks[i].rockSize-1);
					addRock(makePoint((int)gRocks[i].x-2, (int)gRocks[i].y-2),
									randRange(gRocks[i].dx*48+16,0)/64.,
									randRange(gRocks[i].dy*48+16,0)/64.,
									gRocks[i].rockSize-1);
				}
				gRocks[i].status = DEAD;
				break;
			case DEAD:
				break;
		}
	}
	//Update explosions
	for(i = 0; i < MAX_EXPLOSIONS; i++) {
		if(gExplosions[i].status == ALIVE) {
			HWREGBITW(&gFlags, LEVEL_COMPLETE) = False;
			if(gExplosions[i].current++ > gExplosions[i].lifetime) {
				gExplosions[i].status = DEAD;
				continue;
			}
		}
	}
}
void gameSet(short level) { //Gets the game ready for a new level.
	//TODO: Can be updated to use addRock
	int i;
	centerPlayer();
	killBullets();
	killEnemies();
	killExplosions();
	if(level < 5) {
		for(i = 0; i < level; i++) {
			gRocks[i].x = randRange(-10, 10);
			gRocks[i].y = randRange(-10, 10);
			gRocks[i].dx = randRange(-64, 64)/64.;
			gRocks[i].dy = randRange(-64, 64)/64.;
			gRocks[i].status = ALIVE;
			gRocks[i].rockType = randRange(0, 0xF);
			gRocks[i].rockSize = 3;//randRange(1,3);
			if(abs(gRocks[i].dx)-abs(gRocks[i].dy) < 1) {
				gRocks[i].dx = randRange(10, 20)/20.;
				gRocks[i].dy = randRange(10, 20)/20.;
			}
		}
	}
	else if(level < 10) {
		for(i = 0; i < level/2+3; i++) {
			gRocks[i].x = randRange(-10, 10);
			gRocks[i].y = randRange(-10, 10);
			gRocks[i].dx = randRange(-1, 1);
			gRocks[i].dy = randRange(abs(gRocks[i].dx)-1, 1-abs(gRocks[i].dx));
			gRocks[i].status = ALIVE;
			gRocks[i].rockType = randRange(0, 0xF);
			gRocks[i].rockSize = randRange(1,3);
			if(randRange(0, level) > 5) {
				gRocks[i].rockSize = 3;
			}
		}
	}
	//DEBUG:addBullet(makePoint(128/2, 96/2), 2, 2, True);
}
void gameInit(void) {
	centerPlayer();
	killRocks();
	killBullets();
	killEnemies();
	killExplosions();
}
void centerPlayer()	{
	//Set the player in the center.
	gPlayer.x = 128/2;
	gPlayer.y = 96/2;
	gPlayer.dx = 0;
	gPlayer.dy = 0;
	gPlayer.angle = 90;
	gPlayer.status = ALIVE;
	gPlayer.exhaustOn = False;
}
//Object adding functions
void addRock(point rockPos, int dx, int dy, unsigned char rockSize) {
	int i;
	for(i = 0; i < MAX_ROCKS; i++) {
		if(gRocks[i].status == DEAD) {
			gRocks[i].x = rockPos.x;
			gRocks[i].y = rockPos.y;
			gRocks[i].dx = dx;
			gRocks[i].dy = dy;
			gRocks[i].status = ALIVE;
			gRocks[i].rockType = randRange(0, 0xF);
			gRocks[i].rockSize = rockSize;
			return;
		}
	}
}
void addBullet(point bulletPos, int dx, int dy, bool isAllied) {
	int i;
	if(isAllied) {
		for(i = 0; i < MAX_PLAYER_BULLETS; i++) {
			if(gPlayerBullets[i].status == DEAD) {
				gPlayerBullets[i].x = bulletPos.x;
				gPlayerBullets[i].y = bulletPos.y;
				gPlayerBullets[i].dx = dx;
				gPlayerBullets[i].dy = dy;
				gPlayerBullets[i].status = ALIVE;
				gPlayerBullets[i].life = 0;
				return;
			}
		}
	} else {
		for(i = 0; i < MAX_ENEMY_BULLETS; i++) {
			if(gEnemyBullets[i].status == DEAD) {
				gEnemyBullets[i].x = bulletPos.x;
				gEnemyBullets[i].y = bulletPos.y;
				gEnemyBullets[i].dx = dx;
				gEnemyBullets[i].dy = dy;
				gEnemyBullets[i].status = ALIVE;
				gEnemyBullets[i].life = 0;
				return;
			}
		}
	}
}
void addExplosion(point pos, short lifetime) {
	int i;
	for(i = 0; i < MAX_EXPLOSIONS; i++) {
		if(gExplosions[i].status == DEAD) {
			gExplosions[i].pos = pos;
			gExplosions[i].status = ALIVE;
			gExplosions[i].lifetime = lifetime;
			gExplosions[i].current = 0;
			return;
		}
	}
}
//Clearing functions (clear globals)
void killRocks(void) {
	int i;
	//Set all rocks to dead.
	for(i = 0; i < MAX_ROCKS; i++) {
		gRocks[i].x = 0;
		gRocks[i].y = 0;
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
		gPlayerBullets[i].x = 0;
		gPlayerBullets[i].y = 0;
		gPlayerBullets[i].dx = 0;
		gPlayerBullets[i].dy = 0;
		gPlayerBullets[i].status = DEAD;
		gPlayerBullets[i].life = BULLET_LIFETICKS;
	}
	for(i = 0; i < MAX_ENEMY_BULLETS; i++) {
		gEnemyBullets[i].x = 0;
		gEnemyBullets[i].y = 0;
		gEnemyBullets[i].dx = 0;
		gEnemyBullets[i].dy = 0;
		gEnemyBullets[i].status = DEAD;
		gEnemyBullets[i].life = BULLET_LIFETICKS;
	}
}
void killExplosions(void) {
	int i;
	//Set all Explosions to dead.
	for(i = 0; i < MAX_EXPLOSIONS; i++) {
		gExplosions[i].pos = makePoint(0,0);
		gExplosions[i].status = DEAD;
		gExplosions[i].lifetime = 0;
		gExplosions[i].current = 0;
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
