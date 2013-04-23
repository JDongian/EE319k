#include draw2D.h

point* getLine(point a, point b) {
	point *output; int i = 0;
	int dx = abs(b.x-a.x), sx = a.x<b.x ? 1 : -1;
	int dy = abs(b.y-a.y), sy = a.y<b.y ? 1 : -1; 
	int err = (dx>dy ? dx : -dy)/2, e2;
	for(;;) {
		output[i++] = {a.x,a.y};
		if (a.x==b.x && a.y==b.y) break;
		e2 = err;
		if (e2 >-dx) { err -= dy; a.x += sx; }
		if (e2 < dy) { err += dx; a.y += sy; }
	}
	output[i] = {-1, -1};
}

point* createRect(point topLeft, point bottomRight){
	point* rectPoints; int i=0;
	int j;
	if(topLeft.x > bottomRight.x){
		intSwap(&topLeft.x, &bottomRight.x);
	}if(topLeft.y > bottomRight.y){
		intSwap(&topLeft.y, &bottomRight.y);
	}
	top = getLine({topLeft.x, topLeft.y}, {bottomRight.x, topLeft.y});
	right = getLine({bottomRight.x, topLeft.y}, {bottomRight.x, bottomRight.y});
	bottom = getLine({topLeft.x, bottomRight.y}, {bottomRight.x, bottomRight.y});
	left = getLine({topLeft.x, topLeft.y}, {topLeft.x, bottomRight.y});
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

point* rasterCircle(point center, int radius) {
	point* circlePoints; int i = 0;
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;
	//Draw the axis points
	circlePoints[i++] = {center.x, center.y + radius};
	circlePoints[i++] = {center.x, center.y - radius};
	circlePoints[i++] = {center.x + radius, center.y};
	circlePoints[i++] = {center.x - radius, center.y};
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
		circlePoints[i++] = {center.x + x, center.y + y};
		circlePoints[i++] = {center.x - x, center.y + y};
		circlePoints[i++] = {center.x + x, center.y - y};
		circlePoints[i++] = {center.x - x, center.y - y};
		circlePoints[i++] = {center.x + y, center.y + x};
		circlePoints[i++] = {center.x - y, center.y + x};
		circlePoints[i++] = {center.x + y, center.y - x};
		circlePoints[i++] = {center.x - y, center.y - x};
	}
	return circlePoints;
}

point* rotate(point* obj, char angle) {
	point* rotObj; int i = 0;
	char angleInit;
	while(obj[i] != -1) {
		obj[i].x*(1<<20)/obj[i].y;
		rotObj[i] = obj[i];
		i++;
	}
	return rotObj;
}






/*

point* createSegment(point a, point b){
	int i=0;
	short sx = -1;
	short sy = -1;
	short dx = b.x - a.x;
	short dy = b.y - a.y;
	short error = dx-dy;
	short error2 = error*2;
	point* linePoints;
	if (b.x < a.x){sx = 1;}
	if (b.y < a.y){sy = 1;}
	do{
		linePoints[i++] = {a.x, a.y};
		if(error2 > -1*dy){
			error -= dy;
			a.x += sx;
		}
		if(e2 < dx){
			error += dx
			a.y += sy
		}
	}while(b.x != a.x && b.y != a.y);
	return linePoints;
}


point* drawCircle(point center, int radius)
{

  int x = radius, y = 0;
  int xChange = 1 - radius*2;
  int yChange = 0;
  int radiusError = 0;
 
  while(x >= y)
  {
    DrawPixel(x + x0, y + y0);
    DrawPixel(y + x0, x + y0);
    DrawPixel(-x + x0, y + y0);
    DrawPixel(-y + x0, x + y0);
    DrawPixel(-x + x0, -y + y0);
    DrawPixel(-y + x0, -x + y0);
    DrawPixel(x + x0, -y + y0);
    DrawPixel(y + x0, -x + y0);
 
    y++;
    radiusError += yChange;
    yChange += 2;
    if(((radiusError << 1) + xChange) > 0)
    {
      x--;
      radiusError += xChange;
      xChange += 2;
    }
  }
}

*/