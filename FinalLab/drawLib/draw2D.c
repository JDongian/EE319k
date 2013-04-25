#include "draw2D.h"

void drawObj(point* obj, unsigned char shade) {
	int i = 0;
	while(obj[i].x != END) {
		drawPx(obj[i++], shade);
	}
}
void drawPoint(point myPoint, unsigned char shade) {
	drawPx(myPoint, shade);
}
void drawLine(point a, point b, unsigned char shade) {
	point* obj = getLine(a, b);
	drawObj(obj, shade);
}
void drawRect(point topRight, point bottomLeft, unsigned char shade) {
	point* obj = getRect(topRight, bottomLeft);
	drawObj(obj, shade);
}
void drawCircle(point center, int radius, unsigned char shade) {
	point* obj = getCircle(center, radius);
	drawObj(obj, shade);
}
void demo() {
	drawPoint(makePoint(7, 7), 0xF);
//	drawLine(makePoint(4, 8), makePoint(30, 13), 0xF);
//	drawRect(makePoint(4, 8), makePoint(30, 13), 0xF);
//	drawCircle(makePoint(30, 19), 6, 0xF);
}

