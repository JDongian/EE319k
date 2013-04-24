#ifndef EASYPI
#define EASYPI		3.142
#define RAND_M		2147483648
#define RAND_A		1103515245
#define RAND_C		12345
#define END				-1048576
#endif

#include <math.h>

typedef struct pointShaded {
	char x;
	char y;
	char shade;
} pointSh;
typedef struct point {
	int x;
	int y;
} point;

//Math functions
int abs(int);
int roundInt(float);
short roundSho(float);
int fastSqrt(int);		//Return the integer part of the square root.
int dist(point, point);
int rand(int);
int randRange(int, int);
											//Note: Trig functions are scaled by 2**10 for some arbitrary reason.
int sinDeg(short);
short asinDeg(int);
int cosDeg(short);
short acosDeg(int);
int tanDeg(short);
short atanDeg(int);


