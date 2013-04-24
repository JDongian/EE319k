#include "hw_types.h"
#include "math2.h"

//Misc
void intSwap (int*, int*);
//Point functions
point makePoint(int, int);
void addPoint(point*, int, int);		//Inserts a point to a {-1, -1} terminated array.
point* getLine(point, point);
point* getRect(point, point);
point* getCircle(point, int);
point* rotate(point, char, point*);
point* scale(point, float, point*);

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
