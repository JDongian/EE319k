//Basic util functions to aid graphics
#include "graphicsUtil.h"

unsigned char frameBuffer[64*96] = {0};

//Buffer interface functions
unsigned char* getBuffer(void) { return frameBuffer; }
void clearBuffer(void) {		//Sets frameBuffer to black.
	int i;
	for (i = 0; i < 64*96; i++) {
		frameBuffer[i] = 0;
	}
}
void drawPx(point px, unsigned char shade) {
	shade &= 0xF;
	px.x &= 0x7F;
	if(px.x%2 == 0) {			//If px.x is even
		frameBuffer[(px.x>>1)+(px.y*64)] =
			shade<<4 | (frameBuffer[(px.x>>1)+(px.y*64)] & (0xF));
	} else {				//If px.x is odd
		frameBuffer[(px.x>>1)+(px.y*64)] =
			shade | (frameBuffer[(px.x>>1)+(px.y*64)] & 0xF<<4);
	}
}
//Collision detect helpers
box getBox(point* points, int numberOfPoints) {
	point topL = {1<<20,1<<20}; point botR = {0,0}; box fittingBox;
	int i;
	for(i = 0; i < numberOfPoints; i++) {
		if(points[i].x < topL.x) { topL.x = points[i].x; }
		if(points[i].y < topL.y) { topL.y = points[i].y; }
		if(points[i].x > botR.x) { botR.x = points[i].x; }
		if(points[i].y > botR.y) { botR.y = points[i].y; }
	}
	fittingBox.topL = topL;
	fittingBox.botR = botR;
	return fittingBox;
}
bool pointInPolygon(point* verticies, int numberOfVerticies, point test) {
	int i, j;
	bool result = False;
	for(i = 0, j = numberOfVerticies-1; i < numberOfVerticies; j = i++) {
//Float only version, perfect detection.																 
//		if(((verticies[i].y > test.y) != (verticies[j].y > test.y)) &&
//			 ((float)test.x < (float)(verticies[j].x-verticies[i].x)*(test.y-verticies[i].y) /
//															 (verticies[j].y-verticies[i].y)+verticies[i].x)) {
//Integer only version, a bit less accurate.																 
			if(((verticies[i].y > test.y) != (verticies[j].y > test.y)) &&
				 (test.x < (verticies[j].x-verticies[i].x)*(test.y-verticies[i].y) /
									 (verticies[j].y-verticies[i].y)+verticies[i].x)) {
			result ^= 1;
		}
  }
  return result;
	//For more help:
	//http://stackoverflow.com/questions/11716268/point-in-polygon-algorithm
}

//===============Code Graveyard================
/*
pointArr scale(point center, float scaleFactor, pointArr obj){
	pointArr scaleObj; int i = 0;
	while(obj.array[i].x != END) {
		scaleObj.array[i++] = makePoint(scaleFactor*(obj.array[i].x-center.x)+center.x,
																		scaleFactor*(obj.array[i].y-center.y)+center.y);
	}
	scaleObj.array[i] = makePoint(END, END);
	return scaleObj;
}
*/
