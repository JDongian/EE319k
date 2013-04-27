#include "hw_types.h"
#include "math2.h"


//Buffer interface functions
unsigned char* getBuffer(void);   //Returns the current frameBuffer.
void clearBuffer(void);   //Sets frameBuffer to black.
void setBuffer(unsigned char);   //Sets frameBuffer to shade.
void setPx(point, unsigned char);   //Writes to the frameBuffer.
//Graphics modifier
void setGraphics(unsigned char setting); 
	//0 = line
	//1 = int shaded
	//2 = fully shaded
//Collision detect helpers
box getBox(point*, int);  //Finds the minimum fitting box.
bool pointInPolygon(point*, int, point);   //Uses a ray-pairity implemetation.
