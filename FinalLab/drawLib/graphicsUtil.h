//Defines
#define bigNumber 1073741824 //2**30
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

/*typedef struct point3D{
	int x;
	int y;
	int z;
	char shade;
} point3D;*/



//Functions
int sqrt(int);		//Return the integer part of the square root.
int sin20(char);
char arcsin20(int, bool);
int tan20(char);
short arctan20(int, int);
int dist(point, point);
void intSwap (int*, int*);

//Floating point functions
void floatSwap (float*, float*);
float sin(char);
char arcsin(float, bool);
float ipart (float);	//Return the integral part.
float round (float);	//Returt the nearest integer.
float fpart (float);	//Return the fractional part.
float rfpart (float);	//Return 1 - fpart.
float abs (float);		//Return the absolute value.




