#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED

#include<bits/stdc++.h>
#include "Main.h"
using namespace std;


bool isInsideCircle(int circle_x, int circle_y,int rad, int x, int y)
{

    if ((x - circle_x) * (x - circle_x) + (y - circle_y) * (y - circle_y) <= rad * rad)
        return true;
    else
        return false;
}

void Bressenham(int r,int centerX,int centerY,int color)
{
    int d = 3-2*r;
    int tot = round(double(r)/sqrt(2.0));
    int y = round(sqrt(double(r*r-0)));

    for(int i=0;i<=tot;i++)
    {


        drawPixel(PT(i+centerX,y+centerY),color,3);
        drawPixel(PT(i+centerX,-y+centerY),color,3);
        drawPixel(PT(-i+centerX,y+centerY),color,3);
        drawPixel(PT(-i+centerX,-y+centerY),color,3);

        drawPixel(PT(y+centerX,i+centerY),color,3);
        drawPixel(PT(-y+centerX,i+centerY),color,3);
        drawPixel(PT(y+centerX,-i+centerY),color,3);
        drawPixel(PT(-y+centerX,-i+centerY),color,3);

        if(d<0) d += 4*i+6;
        else d+= 4*i-4*y+10;
        if(d>0) y -= 1;

    }
}


#endif // CIRCLE_H_INCLUDED
