#include "draw2D.h"

bool isExhaustOn;

void drawPoint(point myPoint, unsigned char shade) {
	drawPx(myPoint, shade);
}
void drawLine(point a, point b, unsigned char shade) {
	int dx = abs(b.x-a.x), sx = a.x<b.x ? 1 : -1;
	int dy = abs(b.y-a.y), sy = a.y<b.y ? 1 : -1; 
	int err = (dx>dy ? dx : -dy)/2, e2;
	for(;;) {
		drawPx(makePoint(a.x, a.y), shade);
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
void drawCircle(point center, int radius, unsigned char shade) {	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;
	//Draw the axis points.
	drawPx(makePoint(center.x, center.y + radius), shade);
	drawPx(makePoint(center.x, center.y - radius), shade);
	drawPx(makePoint(center.x + radius, center.y), shade);
	drawPx(makePoint(center.x - radius, center.y), shade);
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
		drawPx(makePoint(center.x + x, center.y + y), shade);
		drawPx(makePoint(center.x - x, center.y + y), shade);
		drawPx(makePoint(center.x + x, center.y - y), shade);
		drawPx(makePoint(center.x - x, center.y - y), shade);
		drawPx(makePoint(center.x + y, center.y + x), shade);
		drawPx(makePoint(center.x - y, center.y + x), shade);
		drawPx(makePoint(center.x + y, center.y - x), shade);
		drawPx(makePoint(center.x - y, center.y - x), shade);
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
void drawPlayer(point loc, short angle) {
	point vertex, port, starboard, exhaust;
	vertex = rotPoint(loc, angle, makePoint(loc.x+4, loc.y));
	port = rotPoint(loc, angle, makePoint(loc.x-4, loc.y-4));
	starboard = rotPoint(loc, angle, makePoint(loc.x-4, loc.y+4));
	exhaust = rotPoint(loc, angle, makePoint(loc.x-2, loc.y));
	drawLine(vertex, port, 0xF);
	drawLine(port, exhaust, 0xF);
	drawLine(exhaust, starboard, 0xF);
	drawLine(starboard, vertex, 0xF);
	drawPx(port, 0xF);
	drawPx(starboard, 0xF);
	drawPx(exhaust, 0xF);
}
void demo() {
	drawPoint(makePoint(128/2, 96/2), 0x4);
	drawRect(makePoint(2, 2), makePoint(128-3, 96-3), 0xF);
	drawRect(makePoint(4, 4), makePoint(123, 91), 0xF);
	drawCircle(makePoint(128/2, 96/2), 42, 0xF);
	drawCircle(makePoint(128/2, 96/2), 40, 0xF);
}

