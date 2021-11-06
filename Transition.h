#ifndef TRANSITION_H_INCLUDED
#define TRANSITION_H_INCLUDED


#include<bits/stdc++.h>
#include "Main.h"
using namespace std;


void Make_Transition()
{
    if(toggle_x==3)
    {
        for(int i=tran.size()-1; i>=0; i--)
        {
            drawPixel(tran[i].first,BLACK,1);
            tran[i].first.x+=toggle_x;
            if(abs(tran[i].first.x)==WINDOW_W/2-5) toggle_x==3?toggle_x = -3 : toggle_x = 3;
            drawPixel(tran[i].first,tran[i].second,1);
        }


    }
    else
    {
        for(int i=0; i<tran.size(); i++)
        {
            drawPixel(tran[i].first,BLACK,1);
            tran[i].first.x+=toggle_x;
            if(abs(tran[i].first.x)==WINDOW_W/2-5 || tran[i].first.x==-WINDOW_W/4) toggle_x==3?toggle_x = -3 : toggle_x = 3;
            drawPixel(tran[i].first,tran[i].second,1);
        }


    }

   if(toggle_y==3)
    {
        for(int i=tran.size()-1; i>=0; i--)
        {
            drawPixel(tran[i].first,BLACK,1);
            tran[i].first.y+=toggle_y;
            if(abs(tran[i].first.y)==WINDOW_H/2-5) toggle_y==3?toggle_y = -3 : toggle_y = 3;
            drawPixel(tran[i].first,tran[i].second,1);
        }


    }
    else
    {
        for(int i=0; i<tran.size(); i++)
        {
            drawPixel(tran[i].first,BLACK,1);
            tran[i].first.y+=toggle_y;
            if(abs(tran[i].first.y)==WINDOW_H/2-5) toggle_y==3?toggle_y = -3 : toggle_y = 3;
            drawPixel(tran[i].first,tran[i].second,1);
        }


    }

    counter_x += toggle_x;
    counter_y += toggle_y;
    return ;
}

#endif // TRANSITION_H_INCLUDED
