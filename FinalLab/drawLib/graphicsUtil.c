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
		frameBuffer[(px.x>>1)+(px.y*64)] = shade<<4 | (frameBuffer[(px.x>>1)+(px.y*64)] & (0xF));
	}	else {
		frameBuffer[(px.x>>1)+(px.y*64)] = shade | (frameBuffer[(px.x>>1)+(px.y*64)] & 0xF<<4);
	}
}

//Misc
void intSwap (int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
/*
void clearPointArr(pointArr* dumb) {
	int i;
	for(i=0; i<OBJ_SIZE;){
		(*dumb).array[i++] = makePoint(END, END);
	}
}*/

//Point functions
point makePoint(int x, int y) {
	point temp;
	temp.x = x; temp.y = y;
	return temp;
}
/*
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
}*/

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


