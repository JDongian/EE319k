#include "draw2D.h"

//Sprites
unsigned char bulletSprite[9] = {
	0x00, 0x04, 0x00,
	0x04, 0x0C, 0x04,
	0x00, 0x04, 0x00
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
