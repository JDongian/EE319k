//Defines
#ifndef EASYPI
#define EASYPI	3.1416
#endif
#define RAND_M	2147483648
#define RAND_A	1103515245
#define RAND_C	12345
//#define RAND_MAX ((1U << 31) - 1
#include <math.h>
#include "hw_types.h"

//Typedefs
typedef struct pointShaded {
	char x;
	char y;
	char shade;
} pointSh;
typedef struct point {
	int x;
	int y;
} point;

//Functions
int abs(int);
int roundInt(float);
short roundShort(float);
int fastSqrt(int);		//Return the integer part of the square root.
int sinDeg(short);
short asinDeg(int);
int cosDeg(short);
short acosDeg(int);
int tanDeg(short);
short atanDeg(int);
int dist(point, point);
void intSwap (int*, int*);
//point* combinePoints(point**);		//Combines -1 terminated 
int rand(int);
int randRange(int min, int max);
point makePoint(int, int);
void addPoint(point*, int, int);		//Adds a point to a {-1, -1} terminated array.
//Floating point functions
/*
void floatSwap (float*, float*);
float sin(char);
char arcsin(float, bool);
float ipart (float);	//Return the integral part.
float round (float);	//Returt the nearest integer.
float fpart (float);	//Return the fractional part.
float rfpart (float);	//Return 1 - fpart.
float abs (float);		//Return the absolute value.
*/


