

point* drawLine (point a, point b) { 
	float dx;float dy;
	float xEnd;float yEnd;float xGap;
	float xPx1;float yPx1;float xPx2;float yPx2;
	float yInter;
	int temp;
	int i=0;		//output index
	point* output;	//array of points
	bool isSteep = False;
	isSteep = (abs(b.y - a.y) > abs(b.x - a.y));
	if(isSteep) {	//Make the line no longer steep
		floatSwap(&a.x, &a.y);
		floatSwap(&b.x, &b.y);
	} 
	if (a.x > b.x) {	//Ensure b is first 
		floatSwap(a.x, b.x);
		floatSwap(a.x, b.x);
	}
	dx = b.x - a.x;
	dy = b.y - a.y;
	gradient = dy/dx;

    //Handle endpoint a
	xEnd = round(a.x);
	yEnd = a.y + gradient*(xEnd - a.x);
	xGap = rfpart(a.x + 0.5);
	xPx1 = xEnd;	//Used in the main loop
	yPx1 = ipart(yEnd);
	if(isSteep) {
		output[i++] = {yPx1, xPx1, rfpart(yEnd)*xGap};
		output[i++] = {yPx1+1, xPx1, fpart(yEnd)*xGap};
	} else {
		output[i++] = {xPx1, yPx1, rfpart(yEnd)*xGap};
		output[i++] = {xPx1, yPx1+1, fpart(yEnd)*xGap};
	}
	yInter = yEnd + gradient;	//First y-intersection for the main loop
	//Handle second endpoint
	xEnd = round(b.x);
	yEnd = b.y + gradient*(xEnd - b.x);
	xGap = fpart(b.x + 0.5);
	xPx2 = xEnd;	//Used in the main loop
	yPx2 = ipart(yEnd);
	if (isSteep) {
		output[i++] = {yPx2 , xpxl2, rfpart(yEnd)*xGap};
		output[i++] = {yPx2+1, xpxl2, fpart(yEnd)*xGap};
    } else {
		output[i++] = {xPx2, yPx2, rfpart(yEnd)*xGap};
		output[i++] = {xPx2, yPx2+1, fpart(yEnd)*xGap};
	}
	//Main loop
	for (x from xpxl1 + 1 to xpxl2 - 1) {
		if (isSteep){
			output[i++] = {ipart(yInter) , x, rfpart(yInter));
            output[i++] = {ipart(yInter)+1, x, fpart(yInter));
		} else {
			output[i++] = {x, ipart (intery),  rfpart(intery)};
			output[i++] = {x, ipart (intery)+1, fpart(intery)};
		}
        yInter = yInter + gradient;
	}
}

point* createRect(point topLeft, point bottomRight){
	int i=0;
	int j=0;
	if(topLeft.x > bottomRight.x){
		intSwap(&topLeft.x, &bottomRight.x);
	}if(topLeft.y > bottomRight.y){
		intSwap(&topLeft.y, &bottomRight.y);
	}
	point* rectPoints;
	top = createSegment({topLeft.x, topLeft.y}, {bottomRight.x, topLeft.y});
	right = createSegment({bottomRight.x, topLeft.y}, {bottomRight.x, bottomRight.y});
	bottom = createSegment({topLeft.x, bottomRight.y}, {bottomRight.x, bottomRight.y});
	left = createSegment({topLeft.x, topLeft.y}, {topLeft.x, bottomRight.y});
	for(j=1; j<(topLeft.x-bottomRight.x); j++){
		rectPoints[i++]=top[j];
	}
	for(j=1; j<(topLeft.y-bottomRight.y); j++){
		rectPoints[i++]=right[j];
	}
	for(j=1; j<(topLeft.x-bottomRight.x); j++){
		rectPoints[i++]=bottom[j];
	}
	for(j=1; j<(topLeft.y-bottomRight.y); j++){
		rectPoints[i++]=left[j];
	}
	return rectPoints;
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

void rasterCircle(point center, int xAxis, int yAxis)
{
  int f = 1 - radius;
  int ddF_x = 1;
  int ddF_y = -2 * radius;
  int x = 0;
  int y = radius;
 
  setPixel(x0, y0 + radius);
  setPixel(x0, y0 - radius);
  setPixel(x0 + radius, y0);
  setPixel(x0 - radius, y0);
 
  while(x < y)
  {
    // ddF_x == 2 * x + 1;
    // ddF_y == -2 * y;
    // f == x*x + y*y - radius*radius + 2*x - y + 1;
    if(f >= 0) 
    {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;    
    setPixel(x0 + x, y0 + y);
    setPixel(x0 - x, y0 + y);
    setPixel(x0 + x, y0 - y);
    setPixel(x0 - x, y0 - y);
    setPixel(x0 + y, y0 + x);
    setPixel(x0 - y, y0 + x);
    setPixel(x0 + y, y0 - x);
    setPixel(x0 - y, y0 - x);
  }
}

