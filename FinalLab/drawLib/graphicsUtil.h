#include "hw_types.h"
#include "math2.h"

#ifndef __OBJSTATS__
#define __OBJSTATS__
#define PLAYER_SHADE						0x8
#define PLAYER_EXHAUST_SHADE		0xC
#define PLAYER_EXHAUST_SHADE2		0xA
#define ROCK_TYPES							0x5
#define ROCK_SHADE							0x6
#define ROCK_VERTICIES					7

#endif //__OBJSTATS__

extern point rockShapes[5][ROCK_VERTICIES];

//Buffer interface functions
unsigned char* getBuffer(void);   //Returns the current frameBuffer.
void clearBuffer(void);   //Sets frameBuffer to black.
void setBuffer(unsigned char);   //Sets frameBuffer to shade.
void setPx(point, unsigned char);   //Writes to the frameBuffer.
//Graphics modifier
void setGraphics(unsigned char setting); 
	//0 = line
	//1 = int shaded
	//2 = fully shaded
unsigned char getSetting(void);
//Collision detect helpers
box getBox(point*, int);  //Finds the minimum fitting box.
bool pointInPolygon(point*, int, point);   //Uses a ray-pairity implemetation.
bool pointInRock(point, unsigned char, unsigned char, point);



