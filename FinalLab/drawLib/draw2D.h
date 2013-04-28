#include "graphicsUtil.h"

#define PLAYER_SHADE						0x8
#define PLAYER_EXHAUST_SHADE		0xC
#define PLAYER_EXHAUST_SHADE2		0xA
#define ROCK_SHADE							0x6

#define ROCK_VERTICIES					7

extern bool isExhaustOn;

void drawPoint(point, unsigned char);
void drawLine(point, point, unsigned char);   //Implements Bresenham's algorithm.
void drawRect(point, point, unsigned char);    //For convinience.
void drawFilledRect(point, point, unsigned char);				//Important for enemy entry.
void drawPolygon(point*, int, unsigned char);   //Connect the dots.
void drawFilledPolygon(point*, int, unsigned char); //Checks points in
                                                                                      //the fitting box for pairity.
void drawCircle(point, int, unsigned char);
void drawPlayer(point, short, bool);    //At angle = 0, player faces to the right.
void drawPlayerExhaust(point, short);   //Fun animation
void drawRock(point, unsigned short, unsigned short);
void drawSprite(unsigned char[], point,
								unsigned int, unsigned int);
void drawBullet(point);
void demo(void);
