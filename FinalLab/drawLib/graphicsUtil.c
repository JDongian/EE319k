//Basic util functions to aid graphics
#include "graphicsUtil.h"

unsigned char frameBuffer[64*96] = {0};

//Drawing functions
unsigned char* getBuffer(void) {
	return frameBuffer;
}
void clearBuffer(void) {
	int i;
	for (i = 0; i < 64*96; i++) {
		frameBuffer[i] = 0;
	}
}
void drawPx(point px, unsigned char shade) {
	shade &= 0xF;
	if(px.x%2 == 0) {		//If px.x is even
		frameBuffer[(px.x>>1)+(px.y*64)] = shade<<4 + (frameBuffer[(px.x>>1)+(px.y*64)] & (0xF));
	}	else {
		frameBuffer[(px.x>>1)+(px.y*64)] = shade + (frameBuffer[(px.x>>1)+(px.y*64)] & 0xF<<4);
	}
}

//Misc
void intSwap (int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
void clearPointArr(pointArr* dumb) {
	int i;
	for(i=0; i<OBJ_SIZE;){
		(*dumb).array[i++] = makePoint(END, END);
	}
}

//Point functions
point makePoint(int x, int y) {
	point temp;
	temp.x = x; temp.y = y;
	return temp;
}
void addPoint(point* obj, int x, int y) {//DONOT USE
	point temp; int i;
	temp = makePoint(x, y);
	while(obj[i++].x != -1) {}
	obj[i++] = temp;
	obj[i] = makePoint(END, END);
}
pointArr getLine(point a, point b) {
	pointArr output; int i = 0;
	int dx = abs(b.x-a.x), sx = a.x<b.x ? 1 : -1;
	int dy = abs(b.y-a.y), sy = a.y<b.y ? 1 : -1; 
	int err = (dx>dy ? dx : -dy)/2, e2;
	clearPointArr(&output);
	for(;;) {
		output.array[i++] = makePoint(a.x, a.y);
		if (a.x==b.x && a.y==b.y) { break; }
		e2 = err;
		if (e2 >-dx) { err -= dy; a.x += sx; }
		if (e2 < dy) { err += dx; a.y += sy; }
	}
	return output;
}
pointArr getRect(point topLeft, point botRight){
	pointArr rectPoints; int i=0;
	int j;
	point topRight; point botLeft;
	pointArr top; pointArr right; pointArr bot; pointArr left;
	clearPointArr(&rectPoints);
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
	while(top.array[j].x != END){
		rectPoints.array[i++] = top.array[j++];
	}j = 1;
	while(right.array[j].x != END){
		rectPoints.array[i++] = right.array[j++];
	}j = 0;
	while(bot.array[j].x != END){
		rectPoints.array[i++] = bot.array[j++];
	}j = 1;
	while(left.array[j].x != END){
		rectPoints.array[i++] = left.array[j++];
	}	rectPoints.array[i++] = botLeft;
		rectPoints.array[i++] = makePoint(botLeft.x+1, botLeft.y);
	return rectPoints;
}

pointArr getCircle(point center, int radius) {
	pointArr circlePoints; int i = 0;
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;
	clearPointArr(&circlePoints);
	//Draw the axis points.
	circlePoints.array[i++] = makePoint(center.x, center.y + radius);
	circlePoints.array[i++] = makePoint(center.x, center.y - radius);
	circlePoints.array[i++] = makePoint(center.x + radius, center.y);
	circlePoints.array[i++] = makePoint(center.x - radius, center.y);
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
		circlePoints.array[i++] = makePoint(center.x + x, center.y + y);
		circlePoints.array[i++] = makePoint(center.x - x, center.y - y);
		circlePoints.array[i++] = makePoint(center.x + x, center.y + y);
		circlePoints.array[i++] = makePoint(center.x - x, center.y - y);
		circlePoints.array[i++] = makePoint(center.x + y, center.y + x);
		circlePoints.array[i++] = makePoint(center.x - y, center.y - x);
		circlePoints.array[i++] = makePoint(center.x + y, center.y + x);
		circlePoints.array[i++] = makePoint(center.x - y, center.y - x);
	}
	circlePoints.array[i] = makePoint(END, END);
	return circlePoints;
}

pointArr rotate(point center, char dAngle, pointArr obj) {
	pointArr rotObj; int i = 0;
	char angle; int magnitude;
	while(obj.array[i].x != END) {
		magnitude = dist(center, obj.array[i]);
		angle = atanDeg((obj.array[i].y-center.y)*(1<<10)/(obj.array[i].x-center.x));
		angle += dAngle;
		rotObj.array[i++] = makePoint((magnitude*sinDeg(angle)+center.x), (magnitude*cosDeg(angle)+center.y));
	}
	rotObj.array[i] = makePoint(END, END);
	return rotObj;
}

pointArr scale(point center, float scaleFactor, pointArr obj){
	pointArr scaleObj; int i = 0;
	while(obj.array[i].x != END) {
		scaleObj.array[i++] = makePoint(scaleFactor*(obj.array[i].x-center.x)+center.x,
																		scaleFactor*(obj.array[i].y-center.y)+center.y);
	}
	scaleObj.array[i] = makePoint(END, END);
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


