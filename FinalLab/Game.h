#include "drawLib\math2.h"
#include "lm3s1968.h"
#include "globals.h"

#ifndef __GAMETYPES__
#define __GAMETYPES__
#define PLAYER_ACCEL						0.7
#define PLAYER_TURN_RATE				17
#define MAX_PLAYER_SPEED				4
#define SPEED_DECAY							0.9
#define MAX_BULLET_SPEED				8
#define BULLET_LIFETICKS				10
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
	int dx, dy;
	agentStatus status;		//Agent life status
	agentType type;
	char behavior;
} agentState;

typedef struct playerState {
	float x, y;
	float dx, dy;
	short angle;
	agentStatus status;		//Player life status
	bool exhaustOn;				//Animations on?
} playerState;

typedef struct rockState {
	point pos;
	int dx, dy;
	agentStatus status;
	unsigned char rockType;
	unsigned char rockSize;
} rockState;

typedef struct bulletState {
	float x, y;
	float dx, dy;
	agentStatus status;
	short life;
} bulletState;

typedef struct exposionState {
	point pos;
	int lifetime;
} explosionState;

/*
typedef struct starState {
	point pos;
	short dirY;
	unsigned char shade;
}*/
#endif //__GAMETYPES__


extern short gameLevel;
//extern unsigned char g_boomSprite[][];
extern playerState gPlayer;
extern rockState gRocks[MAX_ROCKS];
extern bulletState gPlayerBullets[MAX_PLAYER_BULLETS];
extern bulletState gEnemyBullets[MAX_ENEMY_BULLETS];
extern agentState gUFOs[MAX_UFOS];
extern agentState gSatellites[MAX_SATELLITES*3];
//extern starState gStars[MAX_STARS];
extern gOxplosions

void gameInit(void); 	//Begin the game.
void gameUpdate(void); 	//Begin the game.
void gameSet(short);
void addRock(point, int, int, unsigned char);
void addBullet(point, int, int, bool);
	//True = player bullet
	//False = enemy bullet
void centerPlayer(void);
void killRocks(void);
void killBullets(void);
void killEnemies(void);

