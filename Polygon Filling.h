#ifndef POLYGON_FILLING_H_INCLUDED
#define POLYGON_FILLING_H_INCLUDED

#include<bits/stdc++.h>
#include "Main.h"
#include "Line.h"
using namespace std;

void scanLine(vector<PT> points,int color)
{
    tran.clear();
    for(int i=0; i<points.size(); i++)
    {
        points[i].x+=counter_x;
        points[i].y+=counter_y;
    }
    vector<EDGE> edges;

    int n=points.size();
    double st = 1e15, en = -1e15;
    unordered_map<double, int>mp;
    for(int i=0; i<n; i++)
    {
        PT a = points[i];
        PT b = points[(i+1)%n];

        if(a.y==b.y) continue;

        EDGE temp;
        temp.y_min = min(a.y,b.y);
        temp.y_max = max(a.y,b.y);
        temp.x_with_y_min = (a.y<b.y)? a.x : b.x;
        temp.m_inv = (b.x-a.x)/(b.y-a.y);

        st = min(st, temp.y_min);
        en = max(en, temp.y_max);

        mp[temp.y_min] = 1;

        edges.push_back(temp);
    }
    sort(edges.begin(),edges.end());
    n = edges.size();

    for(int i=0; i<n; i++)
    {
        if(mp[edges[i].y_max]) edges[i].y_max--;
    }
    for(double y = st; y<= en; y++)
    {
        vector<PT> int_points;
        for(int i=0; i<n; i++)
        {
            if(y>= edges[i].y_min && y <= edges[i].y_max)
            {
                PT tmp;
                tmp.x = edges[i].x_with_y_min;
                tmp.y = y;
                edges[i].x_with_y_min += edges[i].m_inv;
                int_points.push_back(tmp);
            }
        }

        sort(int_points.begin(),int_points.end());

        for(int i=0; i<int_points.size()-1; i+=2)
        {
            drawLine(int_points[i],int_points[i+1],color,2);
        }
    }
}
#endif // POLYGON_FILLING_H_INCLUDED
