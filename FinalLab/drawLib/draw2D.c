#include "draw2D.h"

//

//Sprites
unsigned char bulletSprite[9] = {
	0x00, 0x04, 0x00,
	0x04, 0x0C, 0x04,
	0x00, 0x04, 0x00
};

//Copypasta
const unsigned char valvanoFont[96][5] = {
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

bool isExhaustOn = False;

void drawPoint(point myPoint, unsigned char shade) {
	setPx(makePoint(myPoint.x%128, myPoint.y%96), shade);
}
void drawLine(point a, point b, unsigned char shade) {
	int dx = abs(b.x-a.x), sx = a.x<b.x ? 1 : -1;
	int dy = abs(b.y-a.y), sy = a.y<b.y ? 1 : -1; 
	int err = (dx>dy ? dx : -dy)/2, e2;
	for(;;) {
		drawPoint(makePoint(a.x, a.y), shade);
		if (a.x==b.x && a.y==b.y) { break; }
		e2 = err;
		if (e2 >-dx) { err -= dy; a.x += sx; }
		if (e2 < dy) { err += dx; a.y += sy; }
	}
}
void drawRect(point topLeft, point botRight, unsigned char shade) {
	point topRight; point botLeft;
	if(topLeft.x > botRight.x){
		intSwap(&topLeft.x, &botRight.x);
	}if(topLeft.y > botRight.y){
		intSwap(&topLeft.y, &botRight.y);
	}
	topRight = makePoint(botRight.x, topLeft.y);
	botLeft = makePoint(topLeft.x, botRight.y);
	drawLine(topLeft, topRight, shade);
	drawLine(topRight, botRight, shade);
	drawLine(botLeft, botRight, shade);
	drawLine(topLeft, botLeft, shade);
}
void drawFilledRect(point topLeft, point botRight, unsigned char shade) {
	point topRight; point botLeft;
	if(topLeft.x > botRight.x){
		intSwap(&topLeft.x, &botRight.x);
	}if(topLeft.y > botRight.y){
		intSwap(&topLeft.y, &botRight.y);
	}
	topRight = makePoint(botRight.x, topLeft.y);
	botLeft = makePoint(topLeft.x, botRight.y);
	while(topLeft.y <= botLeft.y) {
		drawLine(topLeft, topRight, shade);
		topLeft = makePoint(topLeft.x, topLeft.y+1);
		topRight = makePoint(topRight.x, topLeft.y);
	}
}
void drawPolygon(point* verticies, int numberOfVerticies, unsigned char shade) {
	int i;
	for(i = 0; i < numberOfVerticies-1; i++) {
		drawLine(verticies[i], verticies[i+1], shade);
	} drawLine(verticies[i], verticies[0], shade);
}
void drawFilledPolygon(point* verticies, int numberOfVerticies, unsigned char shade) {
	int x, y;
	box myBox;
	if(getSetting() == 0) { return; }
	myBox = getBox(verticies, numberOfVerticies);
	for(y = myBox.topL.y; y <= myBox.botR.y; y++){
		for(x = myBox.topL.x; x <= myBox.botR.x; x++){
			if(pointInPolygon(verticies, numberOfVerticies, makePoint(x, y))) {
				drawPoint(makePoint(x, y), shade);
			}
		}
	}
	drawPolygon(verticies, numberOfVerticies, 0xF);
}
void drawCircle(point center, int radius, unsigned char shade) {
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;
	//Draw the axis points.
	drawPoint(makePoint(center.x, center.y + radius), shade);
	drawPoint(makePoint(center.x, center.y - radius), shade);
	drawPoint(makePoint(center.x + radius, center.y), shade);
	drawPoint(makePoint(center.x - radius, center.y), shade);
	while(x < y) {
		// ddF_x == 2 * x + 1;
		// ddF_y == -2 * y;
		// f == x*x + y*y - radius*radius + 2*x - y + 1;
		if(f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		drawPoint(makePoint(center.x + x, center.y + y), shade);
		drawPoint(makePoint(center.x - x, center.y + y), shade);
		drawPoint(makePoint(center.x + x, center.y - y), shade);
		drawPoint(makePoint(center.x - x, center.y - y), shade);
		drawPoint(makePoint(center.x + y, center.y + x), shade);
		drawPoint(makePoint(center.x - y, center.y + x), shade);
		drawPoint(makePoint(center.x + y, center.y - x), shade);
		drawPoint(makePoint(center.x - y, center.y - x), shade);
	}
}
void drawPlayer(point pos, short angle, bool doExhaust) {		//At angle = 0, player faces to the right.
	point vertex, port, starboard, exhaust;
	point myShip[4];
	vertex = rotPoint(pos, angle, makePoint(pos.x+6, pos.y));
	port = rotPoint(pos, angle, makePoint(pos.x-5, pos.y-5));
	starboard = rotPoint(pos, angle, makePoint(pos.x-5, pos.y+5));
	exhaust = rotPoint(pos, angle, makePoint(pos.x-3, pos.y));
	myShip[0] = vertex;
	myShip[1] = port;
	myShip[2] = exhaust;
	myShip[3] = starboard;
	if(getSetting() >= 1) {
		drawFilledPolygon(myShip, 4, PLAYER_SHADE);
	} else {
		drawPolygon(myShip, 4, PLAYER_SHADE);
	}
	if(doExhaust) {
		if(isExhaustOn) {
			drawPlayerExhaust(pos, angle);
		}
		isExhaustOn ^= 1; //Flip the bit.
	}
}
void drawPlayerExhaust(point pos, short angle) {
	point innerVertex, outerVertex, port, starboard, exhaust;
	point innerFire[4], outerFire[4];
	outerVertex = rotPoint(pos, angle, makePoint(pos.x-7, pos.y));
	port = rotPoint(pos, angle, makePoint(pos.x-5, pos.y-3));
	starboard = rotPoint(pos, angle, makePoint(pos.x-5, pos.y+3));
	exhaust = rotPoint(pos, angle, makePoint(pos.x-3, pos.y));
	outerFire[0] = outerVertex;
	outerFire[1] = port;
	outerFire[2] = exhaust;
	outerFire[3] = starboard;
	if(getSetting() >= 1) {
		innerVertex = rotPoint(pos, angle, makePoint(pos.x-5, pos.y));
		innerFire[0] = innerVertex;
		innerFire[1] = port;
		innerFire[2] = exhaust;
		innerFire[3] = starboard;
		drawFilledPolygon(outerFire, 4, PLAYER_EXHAUST_SHADE2);
		drawFilledPolygon(innerFire, 4, PLAYER_EXHAUST_SHADE);
	} else {
		drawLine(outerVertex, port, PLAYER_EXHAUST_SHADE);
		drawLine(outerVertex, starboard, PLAYER_EXHAUST_SHADE);
	}
}
void drawRock(point pos, unsigned short version, unsigned short size) {
	point myRock[ROCK_VERTICIES]; int i = 0;
//	rockagon outRock;
	version %= ROCK_TYPES;
	for(i = 0; i < ROCK_VERTICIES; i++) {
		myRock[i] = makePoint(pos.x+size*rockShapes[version][i].x,
													pos.y+size*rockShapes[version][i].y);
	}
	if(getSetting() >= 1) {
		drawFilledPolygon(myRock, ROCK_VERTICIES, ROCK_SHADE);
	} else {
		drawPolygon(myRock, ROCK_VERTICIES, ROCK_SHADE+randRange(0,1));
	}
//	for(i = 0; i < ROCK_VERTICIES; i++) { outRock.verticies[i] = myRock[i]; }
//	return outRock;
}
void drawSprite(unsigned char sprite[], point pos,
								unsigned int width, unsigned int height) {
	int i,j;
	for (j = 0; j < height; j++) {
		for (i = 0; i < width; i++) {
			drawPoint(makePoint(pos.x+i, pos.y+j), sprite[i+j*width]);
		}
	}
}
void drawUFO(point pos, short scale){
	point topL, topR, midTL, midTR, midBL, midBR, botL, botR;
	point myUFO[8]; 
	topL =	makePoint(pos.x-scale*2, pos.y-3*scale);
	topR =  makePoint(pos.x+scale*2, pos.y-3*scale);
	midTL=	makePoint(pos.x-scale*3, pos.y-1*scale);
	midTR=  makePoint(pos.x+scale*3, pos.y-1*scale);
	midBL=  makePoint(pos.x-scale*6, pos.y+1*scale);
	midBR=  makePoint(pos.x+scale*6, pos.y+1*scale);
	botL =  makePoint(pos.x-scale*4, pos.y+3*scale);
	botR =  makePoint(pos.x+scale*4, pos.y+3*scale);
	myUFO[0] = topL;
	myUFO[1] = topR;
	myUFO[2] = midTR;
	myUFO[3] = midBR;
	myUFO[4] = botR;
	myUFO[5] = botL;
	myUFO[6] = midBL;
	myUFO[7] = midTL;
	drawLine(makePoint(pos.x-scale*3, pos.y-1*scale),
					 makePoint(pos.x+scale*3, pos.y-1*scale),	0xF);
	drawLine(makePoint(pos.x-scale*6, pos.y+1*scale),
					 makePoint(pos.x+scale*6, pos.y+1*scale), 0xF);
	if(getSetting() >= 1) {
		drawFilledPolygon(myUFO, 8, PLAYER_SHADE);
	} else {
		drawPolygon(myUFO, 8, PLAYER_SHADE);
	}
}
void drawExplosion(point pos, short scale) {
	int i;
	point myExplosion[8];
	scale = 5-scale;
	myExplosion[0] = makePoint(pos.x+scale*randRange(0x0, 0x1), pos.y+randRange(0x0, 0x1)*scale);
	myExplosion[1] = makePoint(pos.x+scale*randRange(0x0, 0x1), pos.y-randRange(0x0, 0x1)*scale);
	myExplosion[2] = makePoint(pos.x+scale*randRange(0x1, 0x2), pos.y+randRange(0x1, 0x2)*scale);
	myExplosion[3] = makePoint(pos.x+scale*randRange(0x1, 0x2), pos.y-randRange(0x1, 0x2)*scale);
	myExplosion[4] = makePoint(pos.x-scale*randRange(0x0, 0x2), pos.y+randRange(0x0, 0x2)*scale);
	myExplosion[5] = makePoint(pos.x-scale*randRange(0x0, 0x2), pos.y-randRange(0x0, 0x2)*scale);
	myExplosion[6] = makePoint(pos.x-scale*randRange(0x1, 0x2), pos.y+randRange(0x1, 0x2)*scale);
	myExplosion[7] = makePoint(pos.x-scale*randRange(0x1, 0x2), pos.y-randRange(0x1, 0x2)*scale);
	for(i = 0; i < 8; i++) {
		drawLine(pos, myExplosion[i], randRange(0x4, 0xF));
//		drawPoint(pos, randRange(0x8, 0xF)));
	}
}
void drawBullet(point pos) {
	drawSprite(bulletSprite, makePoint(pos.x-1, pos.y-1), 3, 3);
}

void drawString(char *pcStr, point pos, unsigned char shade) {
	unsigned long ulIdx1, ulIdx2;
	unsigned char ucTemp;
	unsigned char g_pucBuffer[48];
	int cX, cY;
	pos.x %= 128;
	pos.y %= 96;
	shade &= 0xF;
	// Loop while there are more characters in the string.
	while(*pcStr != 0) {
		// Get a working copy of the current character and convert to an
		// index into the character bit-map array.
		ucTemp = *pcStr++ & 0x7f;
		if(ucTemp < ' ') {
			ucTemp = 0;
		} else {
			ucTemp -= ' ';
		}
		// Build and display the character buffer.
		for(ulIdx1 = 0; ulIdx1 < 6; ulIdx1 += 2) {
			// Convert two columns of 1-bit font data into a single data
			// byte column of 4-bit font data.
			for(ulIdx2 = 0; ulIdx2 < 8; ulIdx2++) {
				//Overwrite with black
				g_pucBuffer[ulIdx2] = 0;
				////if(valvanoFont[ucTemp][ulIdx1]) {
				////	drawPoint(makePoint(pos.x+ulIdx1, pos.y+ulIdx2), shade);
				////} else {
				////	drawPoint(makePoint(pos.x+ulIdx1+1, pos.y+ulIdx2), shade);
				////}
				if(valvanoFont[ucTemp][ulIdx1] & (1 << ulIdx2)) {//odd
					g_pucBuffer[ulIdx2] = (shade << 4) & 0xf0;
				}
				if((ulIdx1 < 4) &&
					 (valvanoFont[ucTemp][ulIdx1 + 1] & (1 << ulIdx2))) {//even
					 g_pucBuffer[ulIdx2] |= (shade << 0) & 0x0f;
				}
			}
			// Send this byte column to the display.
			//RITWriteData(g_pucBuffer, 8);
			for(cX = 0; cX < 8; cX++) {
				for(cY = 0; cY < 6; cY++) {
					drawPoint(makePoint(cX, cY), g_pucBuffer[ulIdx2*6+ulIdx1]);
				}
			}
			pos.x += 2;
			// Return if the right side of the display has been reached.
			if(pos.x == 128) {
					return;
			}
		}
	}
}
