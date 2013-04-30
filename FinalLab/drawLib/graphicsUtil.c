//Basic util functions to aid graphics
#include "graphicsUtil.h"
#include "draw2D.h"

unsigned char frameBuffer[64*96] = {0};
unsigned char gGraphicsSetting;
//0 = line
//1 = shaded
//2 = best shaded

point rockShapes[5][ROCK_VERTICIES] = {
	{{0, 5},{4, 2},{4, -1},{1, -3},{-1, -1},{-3, -3},{-4, 0}},
	{{0, 4},{2, 4},{4, 0},{2, -4},{-1, -5},{-3, -2},{-3, 3}},
	{{-1, 4},{1, 4},{4, 1},{3, -4},{1, -2},{-3, -4},{-4, 1}},
	{{-1, 5},{1, 3},{3, 5},{5, 1},{-1, -5},{-4, -3},{-4, 4}},
	{{0, 5},{5, 1},{3, -5},{-1, -5},{-3, -3},{-6, -2},{-2, 1}}
};

////Buffer interface functions
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
////Graphics settings
void setGraphics(unsigned char setting) {
	gGraphicsSetting = setting;
}
unsigned char getSetting(void) {
	return gGraphicsSetting;
}
////Collision detect helpers
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
		if(gGraphicsSetting == 2 &&
						//Float only version, perfect detection.
			 ((verticies[i].y > test.y) != (verticies[j].y > test.y)) &&
			 ((float)test.x < (float)(verticies[j].x-verticies[i].x)*(test.y-verticies[i].y) /
															 (verticies[j].y-verticies[i].y)+verticies[i].x)) {
			result ^= 1;
		}
		else if(//Integer only version, a bit less accurate.																 
						((verticies[i].y > test.y) != (verticies[j].y > test.y)) &&
						(test.x < (verticies[j].x-verticies[i].x)*(test.y-verticies[i].y) /
						(verticies[j].y-verticies[i].y)+verticies[i].x)) {
			result ^= 1;
		}
  }
  return result;
	//See also:
	//http://stackoverflow.com/questions/11716268/point-in-polygon-algorithm
}
bool pointInRock(point pos,
								 unsigned char type, unsigned char size,
								 point test) {
	int i;
//	point hitBox[4];
	point myRock[ROCK_VERTICIES];
	type %= ROCK_TYPES;
	//Avoid negative coordinates for simplicity.
	pos = makePoint((pos.x%128)+128, (pos.y%96)+96);
	test = makePoint((test.x%128)+128, (test.y%96)+96);
	for(i = 0; i < ROCK_VERTICIES; i++) {
		myRock[i] = makePoint(size*rockShapes[type%ROCK_TYPES][i].x+pos.x,
													size*rockShapes[type%ROCK_TYPES][i].y+pos.y);
	}
/*
	//DEBUG CODE
	drawRect(getBox(myRock, ROCK_VERTICIES).topL,
					 getBox(myRock, ROCK_VERTICIES).botR, 0xF);
	drawPoint(pos, 0xF);
	drawPoint(test, 0xF);
*/
	
	return pointInPolygon(myRock, ROCK_VERTICIES, test);

/*	
	hitBox[0] = getBox(myRock, ROCK_VERTICIES).topL;
	hitBox[1] = makePoint(getBox(myRock, ROCK_VERTICIES).botR.x,
												getBox(myRock, ROCK_VERTICIES).topL.y);
	hitBox[2] = getBox(myRock, ROCK_VERTICIES).botR;
	hitBox[3] = makePoint(getBox(myRock, ROCK_VERTICIES).topL.x,
												getBox(myRock, ROCK_VERTICIES).botR.y);
	//return True;
	return pointInPolygon(hitBox, 4, test);
*/
}
bool pointInRockBox(point pos,
										unsigned char type, unsigned char size,
										point test) {
	int i; box myBox;
	point myRock[ROCK_VERTICIES];
	type %= ROCK_TYPES;
	//Avoid negative coordinates for simplicity.
	pos = makePoint((pos.x%128)+128, (pos.y%96)+96);
	test = makePoint((test.x%128)+128, (test.y%96)+96);
	for(i = 0; i < ROCK_VERTICIES; i++) {
		myRock[i] = makePoint(size*rockShapes[type%ROCK_TYPES][i].x+pos.x,
													size*rockShapes[type%ROCK_TYPES][i].y+pos.y);
	}
	myBox = getBox(myRock, ROCK_VERTICIES);
	drawRect(makePoint(test.x-1, test.y-1),
					 makePoint(test.x+1, test.y+1),
					 0xF);
	drawRect(makePoint(pos.x-1, pos.y-1),
					 makePoint(pos.x+1, pos.y+1),
					 0xF);
	if(isBetween(test.x, myBox.topL.x, myBox.botR.x) &&
		 isBetween(test.x, myBox.topL.y, myBox.botR.y)) {
		return True;
	} return False;
}

