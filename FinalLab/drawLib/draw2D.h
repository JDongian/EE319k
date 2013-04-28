#include "graphicsUtil.h"

extern point rocks[5][ROCK_VERTICIES];

extern bool isExhaustOn;

void drawPoint(point, unsigned char);
void drawLine(point, point, unsigned char);   //Implements Bresenham's algorithm.
void drawRect(point, point, unsigned char);    //For convinience.
void drawFilledRect(point, point, unsigned char);				//Important for enemy entry.
void drawPolygon(point*, int, unsigned char);   //Connect the dots.
void drawFilledPolygon(point*, int, unsigned char); //Checks points in
                                                                                      //the fitting box for pairity.
void drawCircle(point, int, unsigned char);
anPlayer drawPlayer(point, short, bool); //At angle = 0, player faces to the right.
void drawBoom(point loc, short scale);
void drawPlayerExhaust(point, short);   //Fun animation
rockagon drawRock(point, unsigned short, unsigned short);
void drawSprite(unsigned char[], point,
								unsigned int, unsigned int);
void drawBullet(point);
void drawExplosion(point, short);
void demo(void);
