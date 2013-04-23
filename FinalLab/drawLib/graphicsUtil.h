//Defines
#ifndef EASYPI
#define EASYPI 3.1416
#endif
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
int fastSqrt(int);		//Return the integer part of the square root.
int sinDeg(short);
short asinDeg(int);
int tanDeg(short);
short atanDeg(int);
int dist(point, point);
void intSwap (int*, int*);

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


