#include <strings.h>
#include "hw_types.h"
#include "math2.h"


//Buffer interface functions
unsigned char* getBuffer(void);   //Returns the current frameBuffer.
void clearBuffer(void);   //Sets frameBuffer to black.
void drawPx(point, unsigned char);   //Writes to the frameBuffer.
//PENDING MOVE///////////////////////////
void intSwap (int*, int*);
point makePoint(int, int);
int crossP(point, point);   //Cross product with respect to the origin
bool isBetween(int, int, int);   //Endpoint inclusive bound check
bool lineIntersect(point, point, point, point);   //**Reliable in case a is horizantal. **BUGGED:a1**
///////////////////////////////////////////
//Collision detect helpers
box getBox(point*, int);  //Finds the minimum fitting box.
bool pointInPolygon(point*, int, point);   //Uses a ray-pairity implemetation.
