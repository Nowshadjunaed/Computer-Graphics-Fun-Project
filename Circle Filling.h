#ifndef CIRCLE_FILLING_H_INCLUDED
#define CIRCLE_FILLING_H_INCLUDED

#include<bits/stdc++.h>
#include "Main.h"
using namespace std;

void BoundaryFill(int curPixelX, int curPixelY, int boundaryColor, int fillColor)
{
    PT pixel = convertPixel(PT(curPixelX,curPixelY));
    int currColor = getpixel(pixel.x, pixel.y);

    if(currColor == boundaryColor || currColor == fillColor) return ;


    drawPixel(PT(curPixelX, curPixelY), fillColor,-1);

    BoundaryFill(curPixelX, curPixelY+1, boundaryColor, fillColor);
    BoundaryFill(curPixelX, curPixelY-1, boundaryColor, fillColor);
    BoundaryFill(curPixelX+1, curPixelY, boundaryColor, fillColor);
    BoundaryFill(curPixelX-1, curPixelY, boundaryColor, fillColor);
}


#endif // CIRCLE_FILLING_H_INCLUDED
