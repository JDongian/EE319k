//Basic util functions to aid graphics
#include "graphicsUtil.h"

unsigned char frameBuffer[64*96] = {0};
unsigned char gGraphicsSetting;
//0 = line
//1 = shaded
//2 = best shaded

//Buffer interface functions
unsigned char* getBuffer(void) { return frameBuffer; }
void clearBuffer(void) {		//Sets frameBuffer to black.
	int i;
	for (i = 0; i < 64*96; i++) {
		frameBuffer[i] = 0;
	}
}
void setBuffer(unsigned char shade) {		//Sets frameBuffer to shade.
	int i;
	for (i = 0; i < 64*96; i++) {
		frameBuffer[i] = (shade<<4) + (shade&0xF);
	}
}
void setPx(point px, unsigned char shade) {
	shade &= 0xF;
	px.x = (px.x+128)%128;
	px.y = (px.y+96)%96;
	if(px.x%2 == 0) {	//If px.x is even
		frameBuffer[(px.x>>1)+(px.y*64)] =
			shade<<4 | (frameBuffer[(px.x>>1)+(px.y*64)] & (0xF));
	} else {					//If px.x is odd
		frameBuffer[(px.x>>1)+(px.y*64)] =
			shade | (frameBuffer[(px.x>>1)+(px.y*64)] & 0xF<<4);
	}
}
//Graphics settings
void setGraphics(unsigned char setting) {
	gGraphicsSetting = setting;
}
unsigned char getSetting(void) {
	return gGraphicsSetting;
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
		if(gGraphicsSetting == 2 &&
			 ((verticies[i].y > test.y) != (verticies[j].y > test.y)) &&
			 ((float)test.x < (float)(verticies[j].x-verticies[i].x)*(test.y-verticies[i].y) /
															 (verticies[j].y-verticies[i].y)+verticies[i].x)) {
			result ^= 1;
		}
//Integer only version, a bit less accurate.																 
		else if(((verticies[i].y > test.y) != (verticies[j].y > test.y)) &&
						(test.x < (verticies[j].x-verticies[i].x)*(test.y-verticies[i].y) /
						(verticies[j].y-verticies[i].y)+verticies[i].x)) {
			result ^= 1;
		}
  }
  return result;
	//See also:
	//http://stackoverflow.com/questions/11716268/point-in-polygon-algorithm
}
bool pointInRock(point* verticies, int numberOfVerticies, point test) {
	int i, j;
	bool result = False;
	point myRock[ROCK_VERTICIES];
	for(i = 0; i < ROCK_VERTICIES; i++) {
		myRock[j] = makePoint(gRockShapes[gRocks[i].rockType%ROCK_TYPES]+gRocks[i].pos.x,
													gRockShapes[gRocks[i].rockType%ROCK_TYPES]+gRocks[i].pos.y
	}
	for(i = 0, j = numberOfVerticies-1; i < numberOfVerticies; j = i++) {
//Float only version, perfect detection.																 
		if(gGraphicsSetting == 2 &&
			 ((verticies[i].y > test.y) != (verticies[j].y > test.y)) &&
			 ((float)test.x < (float)(verticies[j].x-verticies[i].x)*(test.y-verticies[i].y) /
															 (verticies[j].y-verticies[i].y)+verticies[i].x)) {
			result ^= 1;
		}
//Integer only version, a bit less accurate.																 
		else if(((verticies[i].y > test.y) != (verticies[j].y > test.y)) &&
						(test.x < (verticies[j].x-verticies[i].x)*(test.y-verticies[i].y) /
						(verticies[j].y-verticies[i].y)+verticies[i].x)) {
			result ^= 1;
		}
  }
  return result;
}
