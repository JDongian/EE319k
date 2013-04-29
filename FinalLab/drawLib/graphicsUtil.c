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
	pos = makePoint((pos.x%128)+128, (pos.y%96)+128);
	test = makePoint((test.x%128)+128, (test.y%96)+128);
	for(i = 0; i < ROCK_VERTICIES; i++) {
		myRock[i] = makePoint(size*rockShapes[type%ROCK_TYPES][i].x+pos.x,
													size*rockShapes[type%ROCK_TYPES][i].y+pos.y);
	}
	return pointInPolygon(myRock, ROCK_VERTICIES, test);

/*
	hitBox[0] = getBox(myRock, ROCK_VERTICIES).topL;
	hitBox[1] = makePoint(getBox(myRock, ROCK_VERTICIES).botR.x,
												getBox(myRock, ROCK_VERTICIES).topL.y);
	hitBox[2] = getBox(myRock, ROCK_VERTICIES).botR;
	hitBox[3] = makePoint(getBox(myRock, ROCK_VERTICIES).topL.x,
												getBox(myRock, ROCK_VERTICIES).botR.y);
	//DEBUG CODE
	drawRect(hitBox[0], hitBox[2], 0x8);
	
	//return True;
	return pointInPolygon(hitBox, 4, test);
*/
}


/*

///////////////////////////////////////////////////////////////////////////////////////
//WARNING: BAD
///////////////////////////////////////////////////////////////////////////////////////

static const unsigned char g_pucFont[96][5] =
{
    { 0x00, 0x00, 0x00, 0x00, 0x00 }, // " "
    { 0x00, 0x00, 0x4f, 0x00, 0x00 }, // !
    { 0x00, 0x07, 0x00, 0x07, 0x00 }, // "
    { 0x14, 0x7f, 0x14, 0x7f, 0x14 }, // #
    { 0x24, 0x2a, 0x7f, 0x2a, 0x12 }, // $
    { 0x23, 0x13, 0x08, 0x64, 0x62 }, // %
    { 0x36, 0x49, 0x55, 0x22, 0x50 }, // &
    { 0x00, 0x05, 0x03, 0x00, 0x00 }, // '
    { 0x00, 0x1c, 0x22, 0x41, 0x00 }, // (
    { 0x00, 0x41, 0x22, 0x1c, 0x00 }, // )
    { 0x14, 0x08, 0x3e, 0x08, 0x14 }, // *
    { 0x08, 0x08, 0x3e, 0x08, 0x08 }, // +
    { 0x00, 0x50, 0x30, 0x00, 0x00 }, // ,
    { 0x08, 0x08, 0x08, 0x08, 0x08 }, // -
    { 0x00, 0x60, 0x60, 0x00, 0x00 }, // .
    { 0x20, 0x10, 0x08, 0x04, 0x02 }, // /
    { 0x3e, 0x51, 0x49, 0x45, 0x3e }, // 0
    { 0x00, 0x42, 0x7f, 0x40, 0x00 }, // 1
    { 0x42, 0x61, 0x51, 0x49, 0x46 }, // 2
    { 0x21, 0x41, 0x45, 0x4b, 0x31 }, // 3
    { 0x18, 0x14, 0x12, 0x7f, 0x10 }, // 4
    { 0x27, 0x45, 0x45, 0x45, 0x39 }, // 5
    { 0x3c, 0x4a, 0x49, 0x49, 0x30 }, // 6
    { 0x01, 0x71, 0x09, 0x05, 0x03 }, // 7
    { 0x36, 0x49, 0x49, 0x49, 0x36 }, // 8
    { 0x06, 0x49, 0x49, 0x29, 0x1e }, // 9
    { 0x00, 0x36, 0x36, 0x00, 0x00 }, // :
    { 0x00, 0x56, 0x36, 0x00, 0x00 }, // ;
    { 0x08, 0x14, 0x22, 0x41, 0x00 }, // <
    { 0x14, 0x14, 0x14, 0x14, 0x14 }, // =
    { 0x00, 0x41, 0x22, 0x14, 0x08 }, // >
    { 0x02, 0x01, 0x51, 0x09, 0x06 }, // ?
    { 0x32, 0x49, 0x79, 0x41, 0x3e }, // @
    { 0x7e, 0x11, 0x11, 0x11, 0x7e }, // A
    { 0x7f, 0x49, 0x49, 0x49, 0x36 }, // B
    { 0x3e, 0x41, 0x41, 0x41, 0x22 }, // C
    { 0x7f, 0x41, 0x41, 0x22, 0x1c }, // D
    { 0x7f, 0x49, 0x49, 0x49, 0x41 }, // E
    { 0x7f, 0x09, 0x09, 0x09, 0x01 }, // F
    { 0x3e, 0x41, 0x49, 0x49, 0x7a }, // G
    { 0x7f, 0x08, 0x08, 0x08, 0x7f }, // H
    { 0x00, 0x41, 0x7f, 0x41, 0x00 }, // I
    { 0x20, 0x40, 0x41, 0x3f, 0x01 }, // J
    { 0x7f, 0x08, 0x14, 0x22, 0x41 }, // K
    { 0x7f, 0x40, 0x40, 0x40, 0x40 }, // L
    { 0x7f, 0x02, 0x0c, 0x02, 0x7f }, // M
    { 0x7f, 0x04, 0x08, 0x10, 0x7f }, // N
    { 0x3e, 0x41, 0x41, 0x41, 0x3e }, // O
    { 0x7f, 0x09, 0x09, 0x09, 0x06 }, // P
    { 0x3e, 0x41, 0x51, 0x21, 0x5e }, // Q
    { 0x7f, 0x09, 0x19, 0x29, 0x46 }, // R
    { 0x46, 0x49, 0x49, 0x49, 0x31 }, // S
    { 0x01, 0x01, 0x7f, 0x01, 0x01 }, // T
    { 0x3f, 0x40, 0x40, 0x40, 0x3f }, // U
    { 0x1f, 0x20, 0x40, 0x20, 0x1f }, // V
    { 0x3f, 0x40, 0x38, 0x40, 0x3f }, // W
    { 0x63, 0x14, 0x08, 0x14, 0x63 }, // X
    { 0x07, 0x08, 0x70, 0x08, 0x07 }, // Y
    { 0x61, 0x51, 0x49, 0x45, 0x43 }, // Z
    { 0x00, 0x7f, 0x41, 0x41, 0x00 }, // [
    { 0x02, 0x04, 0x08, 0x10, 0x20 }, // "\"
    { 0x00, 0x41, 0x41, 0x7f, 0x00 }, // ]
    { 0x04, 0x02, 0x01, 0x02, 0x04 }, // ^
    { 0x40, 0x40, 0x40, 0x40, 0x40 }, // _
    { 0x00, 0x01, 0x02, 0x04, 0x00 }, // `
    { 0x20, 0x54, 0x54, 0x54, 0x78 }, // a
    { 0x7f, 0x48, 0x44, 0x44, 0x38 }, // b
    { 0x38, 0x44, 0x44, 0x44, 0x20 }, // c
    { 0x38, 0x44, 0x44, 0x48, 0x7f }, // d
    { 0x38, 0x54, 0x54, 0x54, 0x18 }, // e
    { 0x08, 0x7e, 0x09, 0x01, 0x02 }, // f
    { 0x0c, 0x52, 0x52, 0x52, 0x3e }, // g
    { 0x7f, 0x08, 0x04, 0x04, 0x78 }, // h
    { 0x00, 0x44, 0x7d, 0x40, 0x00 }, // i
    { 0x20, 0x40, 0x44, 0x3d, 0x00 }, // j
    { 0x7f, 0x10, 0x28, 0x44, 0x00 }, // k
    { 0x00, 0x41, 0x7f, 0x40, 0x00 }, // l
    { 0x7c, 0x04, 0x18, 0x04, 0x78 }, // m
    { 0x7c, 0x08, 0x04, 0x04, 0x78 }, // n
    { 0x38, 0x44, 0x44, 0x44, 0x38 }, // o
    { 0x7c, 0x14, 0x14, 0x14, 0x08 }, // p
    { 0x08, 0x14, 0x14, 0x18, 0x7c }, // q
    { 0x7c, 0x08, 0x04, 0x04, 0x08 }, // r
    { 0x48, 0x54, 0x54, 0x54, 0x20 }, // s
    { 0x04, 0x3f, 0x44, 0x40, 0x20 }, // t
    { 0x3c, 0x40, 0x40, 0x20, 0x7c }, // u
    { 0x1c, 0x20, 0x40, 0x20, 0x1c }, // v
    { 0x3c, 0x40, 0x30, 0x40, 0x3c }, // w
    { 0x44, 0x28, 0x10, 0x28, 0x44 }, // x
    { 0x0c, 0x50, 0x50, 0x50, 0x3c }, // y
    { 0x44, 0x64, 0x54, 0x4c, 0x44 }, // z
    { 0x00, 0x08, 0x36, 0x41, 0x00 }, // {
    { 0x00, 0x00, 0x7f, 0x00, 0x00 }, // |
    { 0x00, 0x41, 0x36, 0x08, 0x00 }, // }
    { 0x02, 0x01, 0x02, 0x04, 0x02 }, // ~
    { 0x00, 0x00, 0x00, 0x00, 0x00 }
};


void drawString(unsigned char* pcStr, point pos) {
	unsigned long ulIdx1, ulIdx2;
	unsigned char ucTemp;
	while(*pcStr != 0) {
		ucTemp = *pcStr++ & 0x7f;
		if(ucTemp < ' ') {
			ucTemp = 0;
		} else {
			ucTemp -= ' ';
		}
		for(ulIdx1 = 0; ulIdx1 < 6; ulIdx1 += 2) {
			for(ulIdx2 = 0; ulIdx2 < 8; ulIdx2++) {
				frameBuffer[ulIdx2] = 0;
				if(g_pucFont[ucTemp][ulIdx1] & (1 << ulIdx2)) {
					frameBuffer[ulIdx2] = 0xf0;
				}
				if((ulIdx1 < 4) && (g_pucFont[ucTemp][ulIdx1 + 1] & (1 << ulIdx2))) {
					frameBuffer[ulIdx2] |= 0x0f;
				}
			}
			pos.x += 2;
		}
	}
}
	
///////////////////////////////////////////////////////////////////////////////////////

*/


