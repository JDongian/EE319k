#include "hw_types.h"
#include "math2.h"

//Driver interfacing
unsigned char* getBuffer(void);
void clearBuffer(void);
void drawPx(point, unsigned char);
void clearPointArr(pointArr*);
//Misc
void intSwap (int*, int*);
//Point functions
point makePoint(int, int);
void addPoint(point*, int, int);//DONOT USE		//Inserts a point to a {-1, -1} terminated array.
pointArr getLine(point, point);
//pointArr getRect(point, point);
pointArr getCircle(point, int);
pointArr rotate(point, char, pointArr);
pointArr scale(point, float, pointArr);

