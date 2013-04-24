//Basic util functions to aid graphics
#include "graphicsUtil.h"

unsigned char (*frameBuffer)[64*96];

//Drawing functions
unsigned char* getBuffer(void) {
	return *frameBuffer;
}
void clearBuffer(void) {
	unsigned char zeroArray[64*96] = {0};
	*frameBuffer = zeroArray;
}
void drawPx(point px, unsigned char shade) {
	if(px.x%2 == 0) {		//If px.x is even
		*frameBuffer[px.x/2+px.y*96] = shade + (*frameBuffer[px.x/2+px.y*96] & (15<<4));
	}	*frameBuffer[px.x/2+px.y*96] = shade<<4 + (*frameBuffer[px.x/2+px.y*96] & 0xF);
}


//Misc
void intSwap (int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

//Point functions
point makePoint(int x, int y) {
	point temp;
	temp.x = x; temp.y = y;
	return temp;
}
void addPoint(point* obj, int x, int y) {
	point temp; int i;
	temp = makePoint(x, y);
	while(obj[i++].x != -1) {}
	obj[i++] = temp;
	obj[i] = makePoint(END, END);
}
point* getLine(point a, point b) {
	point *output; int i = 0;
	int dx = abs(b.x-a.x), sx = a.x<b.x ? 1 : -1;
	int dy = abs(b.y-a.y), sy = a.y<b.y ? 1 : -1; 
	int err = (dx>dy ? dx : -dy)/2, e2;
	for(;;) {
		output[i++] = makePoint(a.x, a.y);
		if (a.x==b.x && a.y==b.y) { break; }
		e2 = err;
		if (e2 >-dx) { err -= dy; a.x += sx; }
		if (e2 < dy) { err += dx; a.y += sy; }
	}
	output[i] = makePoint(END, END);
	return output;
}

point* getRect(point topLeft, point botRight){
	point* rectPoints; int i=0;
	int j;
	point topRight; point botLeft;
	point* top; point* right; point* bot; point* left;
	if(topLeft.x > botRight.x){
		intSwap(&topLeft.x, &botRight.x);
	}if(topLeft.y > botRight.y){
		intSwap(&topLeft.y, &botRight.y);
	}
	topRight = makePoint(botRight.x, topLeft.y);
	botLeft = makePoint(topLeft.x, botRight.y);
	top = getLine(topLeft, topRight);
	right = getLine(topRight, botRight);
	bot = getLine(botLeft, botRight);
	left = getLine(topLeft, botLeft);
	j = 0;
	while(top[j].x != -1){
		rectPoints[i++]=top[j++];
	}j = 0;
	while(right[j].x != -1){
		rectPoints[i++]=right[j++];
	}j = 0;
	while(bot[j].x != -1){
		rectPoints[i++]=bot[j++];
	}j = 0;
	while(left[j].x != -1){
		rectPoints[i++]=left[j++];
	}
	rectPoints[i] = makePoint(END, END);
	return rectPoints;
}

point* getCircle(point center, int radius) {
	point* circlePoints; int i = 0;
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;
	//Draw the axis points.
	circlePoints[i++] = makePoint(center.x, center.y + radius);
	circlePoints[i++] = makePoint(center.x, center.y - radius);
	circlePoints[i++] = makePoint(center.x + radius, center.y);
	circlePoints[i++] = makePoint(center.x - radius, center.y);
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
		circlePoints[i++] = makePoint(center.x + x, center.y + y);
		circlePoints[i++] = makePoint(center.x - x, center.y - y);
		circlePoints[i++] = makePoint(center.x + x, center.y + y);
		circlePoints[i++] = makePoint(center.x - x, center.y - y);
		circlePoints[i++] = makePoint(center.x + y, center.y + x);
		circlePoints[i++] = makePoint(center.x - y, center.y - x);
		circlePoints[i++] = makePoint(center.x + y, center.y + x);
		circlePoints[i++] = makePoint(center.x - y, center.y - x);
	}
	circlePoints[i] = makePoint(END, END);
	return circlePoints;
}

point* rotate(point center, char dAngle, point* obj) {
	point* rotObj; int i = 0;
	char angle; int magnitude;
	while(obj[i].x != -1) {
		magnitude = dist(center, obj[i]);
		angle = atanDeg((obj[i].y-center.y)*(1<<10)/(obj[i].x-center.x));
		angle += dAngle;
		rotObj[i++] = makePoint((magnitude*sinDeg(angle)+center.x), (magnitude*cosDeg(angle)+center.y));
	}
	rotObj[i] = makePoint(END, END);
	return rotObj;
}

point* scale(point center, float scaleFactor, point* obj){
	point* scaleObj; int i = 0;
	while(obj[i].x != -1) {
		scaleObj[i++] = makePoint(scaleFactor*(obj[i].x-center.x)+center.x,
														scaleFactor*(obj[i].y-center.y)+center.y);
	}
	scaleObj[i] = makePoint(END, END);
	return scaleObj;
}


/*
point* combinePoints(point** objList){
	point* outObj; int i = 0; point temp;
	while(objList[i] != -1)
	return outObj;
}
*/


//Floating point functions
/*
void floatSwap (float* a, float* b) {
	float temp = *a;
	*a = *b;
	*b = temp;
}
float sin(char degree) {
	degree = degree%360;
	if(degree <= 90) {
		return sin1048576[degree]/1048576.0;
	} else if(degree <= 180) {
		return sin1048576[180-degree]/1048576.0;
	} else if(degree <= 270) {
		return -1*sin1048576[180-degree]/1048576.0;
	} else {
		return -1*sin1048576[degree]/1048576.0;
	}
}
char arcsin(float ratio, bool isXneg) {
	return arcsin20((int)ratio*(1<<20), isXneg);
}
float ipart (float x) {return  (float)(long)x;}
float round (float x) {return ipart(x + 0.5);}
float fpart (float x) {return x - (float)(double)x;}
float rfpart (float x) {return 1 - fpart(x);}
float abs (float x) {
	if (x<0) {return -1*x;}
	return x;
}
*/


