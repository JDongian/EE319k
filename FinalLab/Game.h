#include "drawLib\math2.h"

#ifndef __GAMETYPES__
#define __GAMETYPES__
#define MAX_STARS								30
#define MAX_PLAYER_BULLETS			5
#define MAX_ENEMY_BULLETS				4
#define	MAX_UFOS								4
#define	MAX_SATELLITES					2
#define MAX_ROCKS								24

typedef enum {
	PLAYER,
	UFO_SMALL,
	UFO_LARGE,
	SATELLITE
} agentType;

typedef enum {
	ALIVE,
	HIT,
	DEAD
} agentStatus;

typedef struct agentState {
	point pos;
	float dx, dy;
	agentStatus status;		//Agent life status
	agentType type;
	char behavior;
} agentState;

typedef struct playerState {
	float x, y;
	float dx, dy;
	short angle;
	agentStatus status;		//Player life status
	char step;						//Animation state
} playerState;

typedef struct rockState {
	point pos;
	int dx, dy;
	agentStatus status;
	unsigned char rockType;
	unsigned char rockSize;
} rockState;

typedef struct bulletState {
	point pos;
	int dx, dy;
	agentStatus status;
} bulletState;
/*
typedef struct starState {
	point pos;
	short dirY;
	unsigned char shade;
}*/
#endif //__GAMETYPES__

//extern unsigned char g_boomSprite[][];
extern playerState gPlayer;
extern rockState gRocks[MAX_ROCKS];
extern bulletState gPlayerBullets[MAX_PLAYER_BULLETS];
extern bulletState gEnemyBullets[MAX_ENEMY_BULLETS];
extern agentState gUFOs[MAX_UFOS];
extern agentState gSatellites[MAX_SATELLITES*3];
//extern starState gStars[MAX_STARS];


void gameInit(void); 	//Begin the game.

