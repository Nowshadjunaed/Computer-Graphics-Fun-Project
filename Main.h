#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED


#include<bits/stdc++.h>
#define INF 10000
using namespace std;

int counter_x = 0;
int counter_y = 0;
int toggle_x = 0;
int toggle_y = 0;
int FILL_COLOR=BROWN;
const int WINDOW_W = 1500, WINDOW_H = 700;

struct PT
{
    double x, y;
    PT() {}
    PT(double a, double b)
    {
        x = a;
        y = b;
    }

    bool operator < (const PT &p)const
    {
        return x < p.x;
    }
};
vector<pair<PT,int>>tran,circle_tran;
vector<PT>polyg;
struct EDGE
{
    double y_min, y_max,x_with_y_min,m_inv;

    EDGE() {}
    EDGE(double a, double b, double c, double d)
    {
        y_min = a;
        y_max = b;
        x_with_y_min = c;
        m_inv = d;
    }

    bool operator < (const EDGE &p)const
    {
        return y_min < p.y_min;
    }
};
void drawAxis()
{
    for(int i=0; i<WINDOW_H; i++) putpixel(WINDOW_W/2, i, WHITE);
    for(int i=0; i<WINDOW_W; i++) putpixel(i, WINDOW_H/2, WHITE);
}

PT convertPixel(PT p)
{
    p.x += WINDOW_W/2;
    p.y = -p.y;
    p.y += WINDOW_H/2;

    return p;
}
void drawPixel(PT p, int color,int fromWhere=0)
{
    if(fromWhere==0)
    {
        tran.push_back({p,color});
        polyg.push_back(p);
    }
    else if(fromWhere==2)
    {
        tran.push_back({p,color});
    }
    else if(fromWhere==3)
    {
        circle_tran.push_back({p,color});
    }
    p = convertPixel(p);
    putpixel((int)(p.x+0.5), (int)(p.y+0.5), color);
}


#endif // MAIN_H_INCLUDED


