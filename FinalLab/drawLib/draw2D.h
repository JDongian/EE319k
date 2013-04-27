#include "graphicsUtil.h"

#define ROCK_VERTICIES 7

extern bool isExhaustOn;

void drawPoint(point myPoint, unsigned char shade);
void drawLine(point a, point b, unsigned char shade);   //Implements Bresenham's algorithm.
void drawRect(point topLeft, point botRight, unsigned char shade);    //For convinience.
void drawPolygon(point* verticies, int numberOfVerticies, unsigned char shade);   //Connect the dots.
void drawFilledPolygon(point* verticies, int numberOfVerticies, unsigned char shade); //Checks points in
                                                                                      //the fitting box for pairity.
void drawCircle(point center, int radius, unsigned char shade);
point rotPoint(point center, short dAngle, point myPoint); //Non-matrix implementation
void drawPlayer(point loc, short angle);    //At angle = 0, player faces to the right.
void drawPlayerExhaust(point loc, short angle);   //Fun animation
void drawRock(point, unsigned short, unsigned short);

void demo(void);
