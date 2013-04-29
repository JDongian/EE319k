#include "graphicsUtil.h"

extern point rocks[5][ROCK_VERTICIES];

extern bool isExhaustOn;

//Basic vector draw
void drawPoint(point, unsigned char);
void drawLine(point, point, unsigned char);   //Implements Bresenham's algorithm.
void drawRect(point, point, unsigned char);    //For convinience.
void drawFilledRect(point, point, unsigned char);				//Important for enemy entry.
void drawPolygon(point*, int, unsigned char);   //Connect the dots.
void drawFilledPolygon(point*, int, unsigned char); //Checks points in
																										//the fitting box for pairity.
void drawCircle(point, int, unsigned char);
//Special vector draw
anPlayer drawPlayer(point, short, bool);    //At angle = 0, player faces to the right.
void drawPlayerExhaust(point, short);   //Fun animation
void drawRock(point, unsigned short, unsigned short);
void drawExplosion(point, short);
//Sprite draw
void drawSprite(unsigned char[], point,
								unsigned int, unsigned int);
void drawBullet(point);
void drawString(unsigned char*, point);
