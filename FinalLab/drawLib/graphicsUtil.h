#include "hw_types.h"
#include "math2.h"


//Buffer interface functions
unsigned char* getBuffer(void);   //Returns the current frameBuffer.
void clearBuffer(void);   //Sets frameBuffer to black.
void drawPx(point, unsigned char);   //Writes to the frameBuffer.
//Collision detect helpers
box getBox(point*, int);  //Finds the minimum fitting box.
bool pointInPolygon(point*, int, point);   //Uses a ray-pairity implemetation.
