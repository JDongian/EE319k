//Basic util functions to aid graphics
#include "graphicsUtil.h"
#include <strings.h>

unsigned char frameBuffer[64*96] = {0};

//Drawing functions
unsigned char* getBuffer(void) {
	return frameBuffer;
}
void clearBuffer(void) {
	memset(frameBuffer, 0, sizeof frameBuffer);
	/*
	int i;
	for (i = 0; i < 64*96; i++) {
		frameBuffer[i] = 0;
	}*/
}
void drawPx(point px, unsigned char shade) {
	shade &= 0xF;
	px.x &= 0x7F;
	if(px.x%2 == 0) {		//If px.x is even
		frameBuffer[(px.x>>1)+(px.y*64)] =
			shade<<4 | (frameBuffer[(px.x>>1)+(px.y*64)] & (0xF));
	}	else {
		frameBuffer[(px.x>>1)+(px.y*64)] =
			shade | (frameBuffer[(px.x>>1)+(px.y*64)] & 0xF<<4);
	}
}
//Misc
void intSwap (int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
box getBox(point* points, int numberOfPoints) {
	point topL = {1<<20,1<<20}; point botR = {0,0}; box fittingBox;
	int i;
	for(i = 0; i < numberOfPoints; i++) {
		if(points[i].x < topL.x) { topL.x = points[i].x; }
		if(points[i].y < topL.y) { topL.y = points[i].y; }
		if(points[i].x > botR.x) { botR.x = points[i].x; }
		if(points[i].y > botR.y) { botR.y = points[i].y; }
	}
	fittingBox.topL = topL;
	fittingBox.botR = botR;
	return fittingBox;
}
int crossP(point v1, point v2) {
	short angle;
	angle = atan2Deg(v1.x, v1.y) - atan2Deg(v2.x, v2.y);
	return dist(v1, makePoint(0,0))*dist(v2, makePoint(0,0))*sinDeg(angle);
}
//  public domain function by Darel Rex Finley, 2006



//  Determines the intersection point of the line segment defined by points A and B
//  with the line segment defined by points C and D.
//
//  Returns YES if the intersection point was found, and stores that point in X,Y.
//  Returns NO if there is no determinable intersection point, in which case X,Y will
//  be unmodified.

/*
That guy's intersect
bool intersect(float Ax, float Ay,
							 float Bx, float By,
							 float Cx, float Cy,
							 float Dx, float Dy,
							 point* result) {
  float  distAB, elCos, elSin, newX, ABpos;
  //  Fail if either line segment is zero-length.
  if (Ax==Bx && Ay==By || Cx==Dx && Cy==Dy) { return False; }
  //  Fail if the segments share an end-point.
  if (Ax==Cx && Ay==Cy || Bx==Cx && By==Cy
  ||  Ax==Dx && Ay==Dy || Bx==Dx && By==Dy) { return False; }
	
  //Translate the system so that point A is on the origin.
  Bx-=Ax; By-=Ay;
  Cx-=Ax; Cy-=Ay;
  Dx-=Ax; Dy-=Ay;
  //Discover the length of segment A-B.
  distAB=sqrt(Bx*Bx+By*By);
  //Rotate the system so that point B is on the positive X axis.
  elCos=Bx/distAB;
  elSin=By/distAB;
  newX=Cx*elCos+Cy*elSin;
  Cy  =Cy*elCos-Cx*elSin; Cx=newX;
  newX=Dx*elCos+Dy*elSin;
  Dy  =Dy*elCos-Dx*elSin; Dx=newX;
  //Fail if segment C-D doesn't cross line A-B.
  if (Cy<0. && Dy<0. || Cy>=0. && Dy>=0.) { return False; }
  //Discover the position of the intersection point along line A-B.
  ABpos=Dx+(Cx-Dx)*Dy/(Dy-Cy);
  //Fail if segment C-D crosses line A-B outside of segment A-B.
  if (ABpos<0. || ABpos>distAB) { return False; }
  //Apply the discovered position to line A-B in the original coordinate system.
  *result = makePoint(roundSho(Ax+ABpos*elCos), roundSho(Ay+ABpos*elSin));
  return True;
}*/
/*
point intersect(box a, box b) {
	point r, s, qp;
	float t; int crossRS;
	qp = makePoint(b.topL.x-a.topL.x, b.botR.y-a.botR.y);
	r = makePoint(a.botR.x-a.topL.x, a.botR.y-a.topL.y);
	s = makePoint(b.botR.x-b.topL.x, b.botR.y-b.topL.y);
	crossRS = crossP(r, s);
	if(crossRS) {
`		t = crossP(qp, s)/crossRS;
		return makePoint(a.topL.x + (int)(t*r.x), a.topL.y + (int)(t*r.y));
	}
	return makePoint(END, END);
}*/
/*
bool isPointNearLine(point test, point a, point b) {//doesn't work and too slow
	int dy = b.y - a.y;
	int dx = b.x - a.x;
	float estimateX = (float)((test.y - a.y)*dx)/dy + a.x;
	if((test.x - estimateX < 1.0) && (test.x - estimateX > -1.0)) {
		return True;
	} return False;
}*/
bool isBetween(int test, int range0, int range1) {//inclusive
	if(range0 >= range1) {
		intSwap(&range0, &range1);
	}
	if(range0 <= test && test <= range1) {
		return True;
	}	return False;
}
bool lineIntersect(point a0, point a1, point b0, point b1) { //**Reliable in special case.
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

bool pointInPolygon(point* verticies, int numberOfVerticies, point test) {
	int i, nodes=0;
	box myBox; //if(test.y%2*test.x%2){return True;} return False;
	myBox = getBox(verticies, numberOfVerticies);
	for(i = 0; i < numberOfVerticies-1; i++) {
		if(lineIntersect(makePoint(myBox.topL.x, test.y), makePoint(test.x, test.y),
										 verticies[i], verticies[i+1]) ==
										 True) {
//		myBox.topL.x test.y test.x test.y
			nodes++;
		}
	}
	if(lineIntersect(makePoint(myBox.topL.x, test.y), test,
									 verticies[i], verticies[i+1]) ==
									 True) {
		nodes++;
	}

	if(nodes%2 == 1) {
		return True;
	} return False;
}
/*
	//D. Finley's algorithm
	int i, j=numberOfVerticies-1;
	bool oddNodes=False;
	for (i=0; i<numberOfVerticies; i++) {
		if (verticies[i].y < test.y && verticies[j].y >= test.y ||
				verticies[j].y < test.y && verticies[i].y >= test.y ) {
					if ((verticies[i].x + (test.y - verticies[i].y)/
							(verticies[j].y - verticies[i].y)*(verticies[j].x - verticies[i].x))
							< test.x) {
							oddNodes ^= 1;
							//oddNodes = !oddNodes;
					}
		}
    j = i; 
	}
	return oddNodes;
}
*/
/*
	====================================================

	//L. Lagidse's algorithm
	int i, j=numberOfVerticies-1;
	bool oddNodes=False;
	for(i=0; i<numberOfVerticies; i++) {
		if((verticies[i].y < test.y && verticies[j].y >= test.y
		||	verticies[j].y < test.y && verticies[i].y >= test.y)
		&& (verticies[i].x <= test.x || verticies[j].x <= test.x)) {
			oddNodes ^= (verticies[i].x+(test.y-verticies[i].y)/
									(verticies[j].y-verticies[i].y)*
									(verticies[j].x-verticies[i].x) < test.x);
		}
    j=i;
	}
  return oddNodes;
}*/

//Point functions
point makePoint(int x, int y) {
	point temp;
	temp.x = x; temp.y = y;
	return temp;
}
/*
pointArr scale(point center, float scaleFactor, pointArr obj){
	pointArr scaleObj; int i = 0;
	while(obj.array[i].x != END) {
		scaleObj.array[i++] = makePoint(scaleFactor*(obj.array[i].x-center.x)+center.x,
																		scaleFactor*(obj.array[i].y-center.y)+center.y);
	}
	scaleObj.array[i] = makePoint(END, END);
	return scaleObj;
}
*/

