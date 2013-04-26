#ifndef __MYMATH__
#define __MYMATH__
#define EASYPI		3.142
#define RAND_M		2147483648
#define RAND_A		1103515245
#define RAND_C		12345
#define END				-1048576
#endif	//__MYMATH__

#ifndef __POINTS__
#define __POINTS__
typedef struct pointShaded {
	char x;
	char y;
	char shade;
} pointSh;
typedef struct point {
	int x;
	int y;
} point;
typedef struct box {
	point topL;
	point botR;
} box;
#endif //__POINTS__

#include <math.h>

//Basic math
int abs(int);
int fastSqrt(int);		//Returns integral part of the sqrt.
unsigned int dist(point, point);
//Rounding
int roundInt(float);
short roundSho(float);
//LCG random functions
void setSeed(int);
int rand(int);
int randRange(int, int);
//Trig ******WARNING:SLOW******
float sinDeg(short);
short asinDeg(int);
float cosDeg(short);
short acosDeg(int);
float tanDeg(short);
short atan2Deg(int, int);
