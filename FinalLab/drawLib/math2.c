#include "math2.h"

int rseed = 0;

//Math functions
int abs(int x) {
	if(x < 0) {
		return x*-1;
	} return x;
}
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
int fastSqrt(int num) {
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
int dist(point a, point b) {
	int dx = a.x-b.x;
	int dy = a.y-b.y;
	return fastSqrt(dx*dx + dy*dy);
}
void setSeed(int val) {
	rseed = val;
}
int rand(int max) {
	rseed = ((rseed*RAND_A+RAND_C)%RAND_M)%max;
	return rseed;
}
int randRange(int min, int max) {
	return rand(max-min+1)+min;
}
int sinDeg(short deg) {
    return (int)roundInt(sin(deg*EASYPI/180)*1024);
}
short asinDeg(int ratio) {
    return (short)roundSho(asin(ratio/1024.)*180/EASYPI);
}
int cosDeg(short deg) {
    return (int)roundInt(cos(deg*EASYPI/180)*1024);
}
short acosDeg(int ratio) {
    return (short)roundSho(acos(ratio/1024.)*180/EASYPI);
}
int tanDeg(short deg) {
    return (int)roundInt(tan(deg*EASYPI/180)*1024);
}
short atanDeg(int ratio) {
    return (short)roundSho(atan(ratio/1024.)*180/EASYPI);
}

