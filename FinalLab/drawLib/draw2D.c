#include "draw2D.h"

void drawObj(pointArr obj, unsigned char shade) {
	int i = 0;
	while(obj.array[i].x != END) {
		drawPx(obj.array[i++], shade);
	}
}
void drawPoint(point myPoint, unsigned char shade) {
	drawPx(myPoint, shade);
}
void drawLine(point a, point b, unsigned char shade) {
	pointArr thing;
	thing = getLine(a, b);
	drawObj(thing, shade);
}
void drawRect(point topRight, point bottomLeft, unsigned char shade) {
	drawObj(getRect(topRight, bottomLeft), shade);
}
void drawCircle(point center, int radius, unsigned char shade) {
	drawObj(getCircle(center, radius), shade);
}
void demo() {
	drawPoint(makePoint(0, 0), 0xF);
	drawLine(makePoint(4, 4), makePoint(16, 7), 0xF);
	drawRect(makePoint(32, 17), makePoint(36, 23), 0xF);
//	drawCircle(makePoint(30, 19), 6, 0xF);
}

