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
#define OBJ_SIZE		30
typedef struct pointShaded {
	char x;
	char y;
	char shade;
} pointSh;
typedef struct point {
	int x;
	int y;
} point;
typedef struct pointArr {
	point array[OBJ_SIZE];
} pointArr;
#endif //__POINTS__

#include <math.h>

//Math functions
int abs(int);
int roundInt(float);
short roundSho(float);
int fastSqrt(int);		//Return the integer part of the square root.
unsigned int dist(point, point);
void setSeed(int);
int rand(int);
int randRange(int, int);
											//Note: Trig functions are scaled by 2**10 for some arbitrary reason.
float sinDeg(short);
short asinDeg(int);
float cosDeg(short);
short acosDeg(int);
float tanDeg(short);
short atan2Deg(int, int);


