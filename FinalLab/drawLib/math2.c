#include "math2.h"

int rseed = 0;

//Basic math
int abs(int x) {
	if(x < 0) {
		return x*-1;
	} return x;
}
int fastSqrt(int num) {		//Returns integral part of sqrt.
	int res = 0;
	int bit = 1 << 30; // The second-to-top bit is set
	// "bit" starts at the highest power of four <= the argument.
	while (bit > num) { bit >>= 2; }
	while (bit != 0) {
		if (num >= res + bit) {
			num -= res + bit;
			res = (res >> 1) + bit;
		} else { res >>= 1; }
		bit >>= 2;
	}
	return res;
}
unsigned int dist(point a, point b) {
	int dx = a.x-b.x;
	int dy = a.y-b.y;
	return fastSqrt(dx*dx + dy*dy);
}
bool isBetween(int test, int range0, int range1) {//Endpoint inclusive bound check
	if(range0 >= range1) {
		intSwap(&range0, &range1);
	}
	if(range0 <= test && test <= range1) {
		return True;
	}	return False;
}
float floatMod(float f, int m) {
	while(f < 0) { f += m; }
	while(f > m) { f -= m; }
	return f;
}
int easyPow(int n, int exp) {
	int out = 1;
	while(exp-- > 0) {
		out *= n;
	}
	return out;
}
//Vector functions
int crossP(point v1, point v2) {		//Cross product with respect to the origin
	short angle;
	angle = atan2Deg(v1.x, v1.y) - atan2Deg(v2.x, v2.y);
	return dist(v1, makePoint(0,0))*dist(v2, makePoint(0,0))*sinDeg(angle);
}
bool lineIntersect(point a0, point a1, point b0, point b1) { //**Reliable in case a is horizantal. **BUGGED:a1**
	int A0 = a0.x-a1.x, B0 = a1.y-a0.y, C0;//dyX+dxY = C
	int A1 = b0.x-b1.x, B1 = b1.y-b0.y, C1;//a is horizontal scan
	int det = A0*B1 - A1*B0;
	C0 = B0*a0.y-A0*a0.x;
	C1 = B1*b0.y-A1*b0.x;
	if(det == 0) {
		return False;
	} else {
		if(isBetween((B1*C0 - B0*C1)/det, b0.x, b1.x)) {
			return True;
		}
		//y = (A0*C1 - A1*C0)/det
	}
	return False;
}
point rotPoint(point center, short dAngle, point myPoint) {
	float angle; unsigned int magnitude;
	angle = atan2Deg((myPoint.x-center.x), (myPoint.y-center.y));
	magnitude = dist(center, myPoint);
	angle -= dAngle;
	return makePoint((center.x+(magnitude*sinDeg(angle))),
									 (center.y-(magnitude*cosDeg(angle))));
}
point scalePoint(point center, short scaleFactor, point target) {
	target.x *= scaleFactor;
	target.y *= scaleFactor;
	return target;
}
//Memory Handlers
void intSwap (int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
point makePoint(int x, int y) {
	point temp;
	temp.x = x; temp.y = y;
	return temp;
}
//Rounding
int roundInt(float x) {
	if(x < 0) {
		return (int)(x-0.5);
	} return (int)(x+0.5);
}
short roundSho(float x) {
	if(x < 0) {
		return (short)(x-0.5);
	} return (short)(x+0.5);
}
//LCG random functions
void setSeed(int val) {
	rseed = val;
}
int rand(int max) {
	rseed = ((rseed*RAND_A+RAND_C)%RAND_M);
	return rseed%max;
}
int randRange(int min, int max) {
	if(max < min) { intSwap(&min, &max); }
	return rand(max-min+1)+min;
}
//Trig ******WARNING:SLOW******
float sinDeg(short deg) { return sin(deg*EASYPI/180); }
short asinDeg(int ratio) { return roundSho(asin(ratio/1024.)*180/EASYPI); }
float cosDeg(short deg) { return cos(deg*EASYPI/180); }
short acosDeg(int ratio) { return roundSho(acos(ratio/1024.)*180/EASYPI); }
float tanDeg(short deg) { return tan(deg*EASYPI/180); }
short atan2Deg(int x, int y) { return roundSho(atan2(x, y)*180/EASYPI+0.5); }

