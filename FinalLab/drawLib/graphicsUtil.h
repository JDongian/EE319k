#include "hw_types.h"
#include "math2.h"

//Driver interfacing
unsigned char* getBuffer(void);
void clearBuffer(void);
void drawPx(point, unsigned char);
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

