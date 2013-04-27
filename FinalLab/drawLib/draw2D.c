#include "draw2D.h"

bool isExhaustOn = False;
unsigned char gGraphicsSetting;

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
void drawPolygon(point* verticies, int numberOfVerticies, unsigned char shade) {
	int i;
	for(i = 0; i < numberOfVerticies-1; i++) {
		drawLine(verticies[i], verticies[i+1], shade);
	} drawLine(verticies[i], verticies[0], shade);
}
void drawFilledPolygon(point* verticies, int numberOfVerticies, unsigned char shade) {
	int x, y;
	box myBox;
	if(gGraphicsSetting == 0) { return; }
	myBox = getBox(verticies, numberOfVerticies);
	for(y = myBox.topL.y; y <= myBox.botR.y; y++){
		for(x = myBox.topL.x; x <= myBox.botR.x; x++){
			if(pointInPolygon(verticies, numberOfVerticies, makePoint(x, y))) {
				drawPoint(makePoint(x, y), shade);
			}
		}
	}
	drawPolygon(verticies, numberOfVerticies, shade);
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
point rotPoint(point center, short dAngle, point myPoint) {
	float angle; unsigned int magnitude;
	angle = atan2Deg((myPoint.x-center.x), (myPoint.y-center.y));
	magnitude = dist(center, myPoint);
	angle -= dAngle;
	return makePoint((center.x+(magnitude*sinDeg(angle))),
									 (center.y-(magnitude*cosDeg(angle))));
}
void drawPlayer(point loc, short angle) {		//At angle = 0, player faces to the right.
	point vertex, port, starboard, exhaust;
	point myShip[4];
	vertex = rotPoint(loc, angle, makePoint(loc.x+6, loc.y));
	port = rotPoint(loc, angle, makePoint(loc.x-5, loc.y-5));
	starboard = rotPoint(loc, angle, makePoint(loc.x-5, loc.y+5));
	exhaust = rotPoint(loc, angle, makePoint(loc.x-3, loc.y));
	myShip[0] = vertex;
	myShip[1] = port;
	myShip[2] = exhaust;
	myShip[3] = starboard;
	if(gGraphicsSetting >= 1) {
		drawFilledPolygon(myShip, 4, 0x6);
	} else {
		drawPolygon(myShip, 4, 0x6);
	}
	if(isExhaustOn) {
		drawPlayerExhaust(loc, angle);
	}
	isExhaustOn ^= 1; //Flip the bit.
}
void drawPlayerExhaust(point loc, short angle) {
	point innerVertex, outerVertex, port, starboard, exhaust;
	point innerFire[4], outerFire[4];
	outerVertex = rotPoint(loc, angle, makePoint(loc.x-7, loc.y));
	innerVertex = rotPoint(loc, angle, makePoint(loc.x-5, loc.y));
	port = rotPoint(loc, angle, makePoint(loc.x-5, loc.y-3));
	starboard = rotPoint(loc, angle, makePoint(loc.x-5, loc.y+3));
	exhaust = rotPoint(loc, angle, makePoint(loc.x-3, loc.y));
	innerFire[0] = innerVertex;
	innerFire[1] = port;
	innerFire[2] = exhaust;
	innerFire[3] = starboard;
	outerFire[0] = outerVertex;
	outerFire[1] = port;
	outerFire[2] = exhaust;
	outerFire[3] = starboard;
	if(gGraphicsSetting >= 1) {
		drawFilledPolygon(outerFire, 4, 0xA);
		drawFilledPolygon(innerFire, 4, 0xF);
	} else {
		drawLine(outerVertex, port, 0xF);
		drawLine(outerVertex, starboard, 0xF);
	}
}	
void demo() {
	point triangle[3];
	point square[4];
	point pentagon[5];
	point hexagon[6];
	
	triangle[0] = makePoint(12, 75);
	triangle[1] = makePoint(10, 70);
	triangle[2] = makePoint(14, 70);
	
	square[0] = makePoint(100, 10);
	square[1] = makePoint(103, 10);
	square[2] = makePoint(103, 13);
	square[3] = makePoint(100, 13);
	
	pentagon[0] = makePoint(15, 10);
	pentagon[1] = makePoint(6, 19);
	pentagon[2] = makePoint(10, 30);
	pentagon[3] = makePoint(21, 30);
	pentagon[4] = makePoint(25, 19);
	
	hexagon[0] = makePoint(80, 60);
	hexagon[1] = makePoint(85, 40);
	hexagon[5] = makePoint(60, 70);
	hexagon[2] = makePoint(88, 70);
	hexagon[4] = makePoint(80, 70);
	hexagon[3] = makePoint(96, 82);
	
	drawPoint(makePoint(128/2, 96/2), 0x2);
	drawRect(makePoint(2, 2), makePoint(128-3, 96-3), 0x2);
	drawRect(makePoint(0, 0), makePoint(127, 95), 0x4);
//	drawRect(makePoint(2, 2), makePoint(24, 10), 0x0);
//	drawRect(makePoint(0, 0), makePoint(24, 10), 0x0);
	drawCircle(makePoint(128/2, 96/2), 8, 0x2);
	drawCircle(makePoint(128/2, 96/2), 10, 0x4);

	drawPolygon(square, 4, 0x1);
	drawFilledPolygon(square, 4, 0x1);
	
	drawPoint(makePoint(0x67,0x0D), 0x8);
	
	drawPolygon(triangle, 3, 0x1);
	drawFilledPolygon(triangle, 3, 0x1);

	drawPolygon(hexagon, 6, 0x1);
	drawFilledPolygon(hexagon, 6, 0x1);

	drawPolygon(pentagon, 5, 0x1);
	drawFilledPolygon(pentagon, 5, 0x1);	
}

