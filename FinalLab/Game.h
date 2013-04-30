#include "drawLib\math2.h"
#include "lm3s1968.h"
#include "globals.h"
#include "sound.h"
#include "drawLib\graphicsUtil.h"

#ifndef __GAMETYPES__
#define __GAMETYPES__
#define PLAYER_ACCEL						0.7
#define PLAYER_TURN_RATE				6
#define MAX_PLAYER_SPEED				1.4
#define SPEED_DECAY							0.92
#define MAX_BULLET_SPEED				3
#define BULLET_LIFETICKS				60
#define MAX_PLAYER_BULLETS			5
#define MAX_ENEMY_BULLETS				4
#define	MAX_UFOS								4
#define	MAX_SATELLITES					2
#define MAX_ROCKS								24
#define MAX_EXPLOSIONS					8

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
	float x, y;
	float dx, dy;
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

typedef struct explosionState {
	point pos;
	agentStatus status;
	short lifetime;
	short current;
} explosionState;

#endif //__GAMETYPES__


extern short gameLevel;

extern playerState gPlayer;
extern rockState gRocks[MAX_ROCKS];
extern bulletState gPlayerBullets[MAX_PLAYER_BULLETS];
extern bulletState gEnemyBullets[MAX_ENEMY_BULLETS];
extern agentState gUFOs[MAX_UFOS];
extern agentState gSatellites[MAX_SATELLITES*3];
extern explosionState gExplosions[MAX_EXPLOSIONS];

void gameInit(void); 	//Begin the game.
void gameUpdate(void); 	//Begin the game.
void gameSet(short);
void addRock(point, int, int, unsigned char);
void addBullet(point, int, int, bool);
	//True = player bullet
	//False = enemy bullet
void addExplosion(point, short);
void centerPlayer(void);
void killRocks(void);
void killBullets(void);
void killEnemies(void);
void killExplosions(void);

