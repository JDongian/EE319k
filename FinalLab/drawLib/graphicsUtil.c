//Basic util functions to aid graphics
#include "graphicsUtil.h"

int fastSqrt(int num) {
    int res = 0;
    int bit = 1 << 30; // The second-to-top bit is set
    // "bit" starts at the highest power of four <= the argument.
    while (bit > num)
        bit >>= 2;
    while (bit != 0) {
        if (num >= res + bit) {
            num -= res + bit;
            res = (res >> 1) + bit;
        }
        else{
            res >>= 1;
		}
        bit >>= 2;
    }
    return res;
}
int sinDeg(short deg) {
    return (int)(sin(deg*EASYPI/180)*1024+0.5);
}
short asinDeg(int ratio) {
    return (short)round(asin(ratio/1024.)*180/EASYPI);
}
int cosDeg(short deg) {
    return (int)(cos(deg*EASYPI/180)*1024+0.5);
}
short acosDeg(int ratio) {
    return (short)round(acos(ratio/1024.)*180/EASYPI);
}
int tanDeg(short deg) {
    return (int)(tan(deg*EASYPI/180)*1024+0.5);
}
short atanDeg(int ratio) {
    return (short)round(atan(ratio/1024.)*180/EASYPI);
}
int dist(point a, point b) {
	int dx = a.x-b.x;
	int dy = a.y-b.y;
	return fastSqrt(dx*dx + dy*dy);
}
void intSwap (int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

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


