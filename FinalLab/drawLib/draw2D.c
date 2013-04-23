#include "draw2D.h"

point* getLine(point a, point b) {
	point *output; int i = 0; point temp;
	int dx = abs(b.x-a.x), sx = a.x<b.x ? 1 : -1;
	int dy = abs(b.y-a.y), sy = a.y<b.y ? 1 : -1; 
	int err = (dx>dy ? dx : -dy)/2, e2;
	for(;;) {
		temp.x = a.x; temp.y = a.y;
		output[i++] = temp;
		if (a.x==b.x && a.y==b.y) { break; }
		e2 = err;
		if (e2 >-dx) { err -= dy; a.x += sx; }
		if (e2 < dy) { err += dx; a.y += sy; }
	}
	temp.x = -1; temp.y = -1;
	output[i] = temp;
	return output;
}

point* getRect(point topLeft, point bottomRight){
	point* rectPoints; int i=0;
	int j;
	point topRight; point bottomLeft;
	point* top; point* right; point* bottom; point* left;
	if(topLeft.x > bottomRight.x){
		intSwap(&topLeft.x, &bottomRight.x);
	}if(topLeft.y > bottomRight.y){
		intSwap(&topLeft.y, &bottomRight.y);
	}
	topRight.x = bottomRight.x; topRight.y = topLeft.y;
	bottomLeft.x = topLeft.x; bottomLeft.y = bottomRight.y;
	top = getLine(topLeft, topRight);
	right = getLine(topRight, bottomRight);
	bottom = getLine(bottomLeft, bottomRight);
	left = getLine(topLeft, bottomLeft);
	j = 0;
	while(top[j].x != -1){
		rectPoints[i++]=top[j++];
	}j = 0;
	while(right[j].x != -1){
		rectPoints[i++]=right[j++];
	}j = 0;
	while(bottom[j].x != -1){
		rectPoints[i++]=bottom[j++];
	}j = 0;
	while(left[j].x != -1){
		rectPoints[i++]=left[j++];
	}
	return rectPoints;
}

point* getCircle(point center, int radius) {
	point* circlePoints; int i = 0; point temp;
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;
	//Draw the axis points
	temp.x = center.x; temp.y = center.y + radius;
	circlePoints[i++] = temp;
	temp.x = center.x; temp.y = center.y - radius;
	circlePoints[i++] = temp;
	temp.x = center.x + radius; temp.y = center.y;
	circlePoints[i++] = temp;
	temp.x = center.x - radius; temp.y = center.y;
	circlePoints[i++] = temp;
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
		temp.x = center.x + x; temp.y = center.y + y;
		circlePoints[i++] = temp;
		temp.x = center.x - x; temp.y = center.y - y;
		circlePoints[i++] = temp;
		temp.x = center.x + x; temp.y = center.y + y;
		circlePoints[i++] = temp;
		temp.x = center.x - x; temp.y = center.y - y;
		circlePoints[i++] = temp;
		temp.x = center.x + y; temp.y = center.y + x;
		circlePoints[i++] = temp;
		temp.x = center.x - y; temp.y = center.y - x;
		circlePoints[i++] = temp;
		temp.x = center.x + y; temp.y = center.y + x;
		circlePoints[i++] = temp;
		temp.x = center.x - y; temp.y = center.y - x;
		circlePoints[i++] = temp;
	}
	return circlePoints;
}

point* rotate(point* obj, char angle) {/*
	point* rotObj; int i = 0;
	char angleInit;
	while(obj[i].x != -1) {
		obj[i].x*(1<<20)/obj[i].y;
		rotObj[i] = obj[i];
		i++;
	}
	return rotObj;*/return 0;
}
