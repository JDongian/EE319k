//Datatypes
typedef struct pointShaded {
	char x;
	char y;
	char shade;
} pointSh;
typedef struct point {
	char x;
	char y;
} point;
typedef enum {True, False} bool;

//Defines
#define bigNumber 1073741824

//Functions
int sqrt(int);		//Return the integer part of the square root.
int sin20(char);
char arcsin20(int);
int tan20(char);
char arctan20(int);
char dist(point, point);
void intSwap (int*, int*);

//Floating point functions
void floatSwap (float*, float*);
float sin(char);
char arcsin(float);
float ipart (float);	//Return the integral part.
float round (float);	//Returt the nearest integer.
float fpart (float);	//Return the fractional part.
float rfpart (float);	//Return 1 - fpart.
float abs (float);		//Return the absolute value.




