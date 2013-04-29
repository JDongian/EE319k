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
#include "hw_types.h"

extern int rseed;

//Basic math
int abs(int);
int fastSqrt(int);		//Returns integral part of the sqrt.
unsigned int dist(point, point);
float floatMod(float, int);
//Vector functions
int crossP(point, point);   //Cross product with respect to the origin
bool isBetween(int, int, int);   //Endpoint inclusive bound check
bool lineIntersect(point, point, point, point);   //**Reliable in case a is horizantal. **BUGGED:a1**
point rotPoint(point, short, point); //Non-matrix implementation
point scalePoint(point, short, point);



//Memory handlers
void intSwap (int*, int*);
point makePoint(int, int);
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
