#include "draw2D.h"

void drawObj(point* obj) {
	int i = 0;
	while(obj[i].x != END) {
		drawPx(obj[i++]);
	}
}
void drawLine(point a, point b) {
	point* obj = getLine(a, b);
	drawObj(obj);
}
void drawRect(point topRight, point bottomLeft) {
	point* obj = getRect(topRight, bottomLeft);
	drawObj(obj);
}
void drawCircle(point center, int radius) {
	point* obj = getCircle(center, radius);
	drawObj(obj);
}
void demo() {
	drawLine(makePoint(4, 8), makePoint(30, 13));
	drawRect(makePoint(4, 8), makePoint(30, 13));
	drawCircle(makePoint(30, 19), 6);
}

