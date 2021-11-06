#ifndef POLYGON_H_INCLUDED
#define POLYGON_H_INCLUDED

#include<bits/stdc++.h>
#include "Main.h"
using namespace std;

void drawPolygon(vector<PT> points,int col)
{
    int n = points.size();
    for(int i=0; i<n; i++)
    {
        drawLine(points[i], points[(i+1)%n],col);
    }
}

bool onSegment(PT p, PT q, PT r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
            q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;
    return false;
}

int orientation(PT p, PT q, PT r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;
    return (val > 0)? 1: 2;
}

bool doIntersect(PT p1, PT q1, PT p2, PT q2)
{

    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);


    if (o1 != o2 && o3 != o4)
        return true;


    if (o1 == 0 && onSegment(p1, p2, q1)) return true;


    if (o2 == 0 && onSegment(p1, q2, q1)) return true;


    if (o3 == 0 && onSegment(p2, p1, q2)) return true;


    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}
bool isInside(vector<PT>polygon, int n, PT p)
{

    for(int i=0;i<polygon.size();i++)
    {
        polygon[i].x += counter_x;
        polygon[i].y += counter_y;
    }
    if (n < 3) return false;


    PT extreme = PT(INF, p.y);


    int count = 0, i = 0;
    do
    {
        int next = (i+1)%n;


        if (doIntersect(polygon[i], polygon[next], p, extreme))
        {

            if (orientation(polygon[i], p, polygon[next]) == 0)
                return onSegment(polygon[i], p, polygon[next]);

            count++;
        }
        i = next;
    }
    while (i != 0);
    return count&1;
}

#endif // POLYGON_H_INCLUDED
