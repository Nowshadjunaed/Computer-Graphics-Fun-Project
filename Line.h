#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED

#include<bits/stdc++.h>
#include "Main.h"
using namespace std;

void drawLine(PT a, PT b,int col,int fromWhere=0)
{

    if(a.y == b.y)
    {
        if(a.x>b.x) swap(a,b);
        for(int x = a.x; x <= b.x; x++)
        {
            drawPixel(PT(x, a.y), col,fromWhere);
        }
    }


    else if(a.x == b.x)
    {
        if(a.y > b.y) swap(a, b);
        for(int y = a.y; y <= b.y; y++)
        {
            drawPixel(PT(a.x, y), col,fromWhere);
        }
    }

    else
    {
        double m = (double)(b.y-a.y)/(double)(b.x-a.x);
        double m_inv  = 1.0/m;
        if(fabs(m)<=1.0)
        {
            if(a.x>b.x) swap(a,b);
            while(a.x<=b.x)
            {
                drawPixel(a,col,fromWhere);
                a.x+=1;
                a.y+=m;
            }
        }
        else
        {
            if(a.y>b.y) swap(a,b);
            while(a.y<=b.y)
            {
                drawPixel(a,col,fromWhere);
                a.x += m_inv;
                a.y+=1;
            }
        }

    }
}



#endif // LINE_H_INCLUDED
