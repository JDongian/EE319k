//Basic util functions to aid graphics
#include "graphicsUtil.h"

//Sin table from 2**20*sin(0) to 2**20*sin(90)
const int sin1048576[] = {0, 18300, 36595, 54878, 73145, 91389, 109606,
127789, 145934, 164033, 182083, 200078, 218011, 235878, 253673, 271391,
289027, 306574, 324028, 341383, 358634, 375776, 392803, 409711, 426494,
443147, 459665, 476044, 492277, 508360, 524288, 540057, 555661, 571095,
586356, 601438, 616338, 631049, 645568, 659890, 674012, 687928, 701634,
715127, 728402, 741455, 754282, 766880, 779244, 791370, 803256, 814897,
826289, 837430, 848316, 858943, 869309, 879410, 889243, 898805, 908093,
917105, 925838, 934288, 942454, 950333, 957922, 965219, 972223, 978930,
985339, 991448, 997255, 1002758, 1007956, 1012847, 1017429, 1021701,
1025662, 1029311, 1032646, 1035666, 1038371, 1040760, 1042832, 1044586,
1046022, 1047139, 1047937, 1048416, 1048576};

const int tan1048576[] = {0, 18303, 36617, 54954, 73324, 91739, 110210,
128749, 147368, 166078, 184892, 203823, 222882, 242083, 261439, 280965,
300674, 320582, 340703, 361054, 381650, 402511, 423652, 445094, 466856,
488959, 511425, 534276, 557538, 581235, 605396, 630048, 655223, 680953,
707273, 734221, 761835, 790159, 819237, 849120, 879860, 911513, 944142,
977813, 1012598, 1048576, 1085832, 1124460, 1164562, 1206249, 1249644,
1294884, 1342116, 1391507, 1443241, 1497522, 1554578, 1614665, 1678072,
1745124, 1816187, 1891681, 1972085, 2057946, 2149899, 2248678, 2355140,
2470290, 2595317, 2731634, 2880939, 3045286, 3227185, 3429738, 3656819,
3913339, 4205609, 4541882, 4933162, 5394456, 5946770, 6620448, 7461006,
8539966, 9976534, 11985279, 14995335, 20008022, 30027288, 60072879};

int sqrt(int num) {
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
int sin20(char degree) {
	degree = degree%360;
	if(degree <= 90) {
		return sin1048576[degree];
	} else if(degree <= 180) {
		return sin1048576[180-degree];
	} else if(degree <= 270) {
		return -1*sin1048576[180-degree];
	} else {
		return -1*sin1048576[degree];
	}
}
char arcsin20(int ratio, bool xIsPositive) {
	int i = 0;
	bool isNeg = False;
	if(ratio < 0) {
		isNeg = True;
		ratio = -1*ratio;
	}
	while(ratio > sin20(i)) {
		if(i++ == 90) { return 90*(isNeg*2-1); }
	}
	if((sin20(i) - ratio) > (ratio - sin20(i-1))) { i--; }
	if(isNeg) { i *= -1; }
	if(xIsPositive) { return i; }
	return 180-i;
}
int tan20(char degree) {
	degree = degree%180;
	if(degree == 90) {
		return bigNumber;
	}
	if(degree < 90) {
		return tan1048576[degree];
	} else {
		return tan1048576[180-degree];
	}
}
short arctan20(int x, int y) { //Unreliable
	int ratio;
	bool isNeg = False;
	short testAngle = 0;
	if(y == 0) {
		if(x > 0) { return 90; }
		return 270;
	}
	ratio = x*(1<<20)/y;
	if(ratio < 0) {
		isNeg = True;
		ratio = -1*ratio;
	}
	while(ratio > tan20(testAngle)) {
		if(testAngle++ == 90) { return 90*(isNeg*2-1); }
	}
	if((tan20(testAngle) - ratio) > (ratio - tan20(testAngle-1))) { testAngle--; }
	if(isNeg) { return 90-testAngle; }
	return testAngle;
}
int dist(point a, point b) {
	int dx = a.x-b.x;
	int dy = a.y-b.y;
	return sqrt(dx*dx + dy*dy);
}
void intSwap (int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

//Floating point functions
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

