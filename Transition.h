#ifndef TRANSITION_H_INCLUDED
#define TRANSITION_H_INCLUDED


#include<bits/stdc++.h>
#include "Main.h"
using namespace std;


void Make_Transition()
{
    if(toggle_x==increament)
    {
        for(int i=tran.size()-1; i>=0; i--)
        {
            drawPixel(tran[i].first,BLACK,1);
            drawPixel(PT(tran[i].first.x-1,tran[i].first.y),BLACK,1);
            tran[i].first.x+=toggle_x;
            if(abs(tran[i].first.x)==WINDOW_W/2-5)
            {
                toggle_x==increament?toggle_x = -increament : toggle_x = increament;
                setbkcolor(LIGHTGREEN);
                setcolor(BLACK);
                BoundaryFill(prvs_circle.x,prvs_circle.y,GREEN,LIGHTGREEN);
                outtextxy(prvs_txt.x,prvs_txt.y,prvs_str);
                setbkcolor(LIGHTBLUE);
                BoundaryFill(-600,-200,GREEN,LIGHTBLUE);
                outtextxy(160,560,"L");
                prvs_circle = PT(-600,-200);
                prvs_txt = PT(160,560);
                prvs_str[0] = 'L';
            }
            drawPixel(tran[i].first,tran[i].second,1);
        }


    }
    else
    {
        for(int i=0; i<tran.size(); i++)
        {
            drawPixel(tran[i].first,BLACK,1);
            drawPixel(PT(tran[i].first.x+1,tran[i].first.y),BLACK,1);
            tran[i].first.x+=toggle_x;
            if(abs(tran[i].first.x)==WINDOW_W/2-5 || tran[i].first.x==-WINDOW_W/4)
            {
                toggle_x==increament?toggle_x = -increament : toggle_x = increament;

                setbkcolor(LIGHTGREEN);
                setcolor(BLACK);
                BoundaryFill(prvs_circle.x,prvs_circle.y,GREEN,LIGHTGREEN);
                outtextxy(prvs_txt.x,prvs_txt.y,prvs_str);
                setbkcolor(LIGHTBLUE);
                BoundaryFill(-480,-200,GREEN,LIGHTBLUE);
                outtextxy(280,560,"R");
                prvs_circle = PT(-480,-200);
                prvs_txt = PT(280,560);
                prvs_str[0] = 'R';
            }
            drawPixel(tran[i].first,tran[i].second,1);
        }


    }

   if(toggle_y==increament)
    {
        for(int i=tran.size()-1; i>=0; i--)
        {
            drawPixel(tran[i].first,BLACK,1);
            drawPixel(PT(tran[i].first.x,tran[i].first.y-1),BLACK,1);
            tran[i].first.y+=toggle_y;
            if(abs(tran[i].first.y)==WINDOW_H/2-20)
            {
                toggle_y==increament?toggle_y = -increament : toggle_y = increament;
                setbkcolor(LIGHTGREEN);
                setcolor(BLACK);
                BoundaryFill(prvs_circle.x,prvs_circle.y,GREEN,LIGHTGREEN);
                outtextxy(prvs_txt.x,prvs_txt.y,prvs_str);
                setbkcolor(LIGHTBLUE);
                BoundaryFill(-540,-260,GREEN,LIGHTBLUE);
                outtextxy(220,620,"D");
                prvs_circle = PT(-540,-260);
                prvs_txt = PT(220,620);
                prvs_str[0] = 'D';
            }
            drawPixel(tran[i].first,tran[i].second,1);
        }


    }
    else
    {
        for(int i=0; i<tran.size(); i++)
        {
            drawPixel(tran[i].first,BLACK,1);
            drawPixel(PT(tran[i].first.x,tran[i].first.y+1),BLACK,1);
            tran[i].first.y+=toggle_y;
            if(abs(tran[i].first.y)==WINDOW_H/2-20)
            {
                toggle_y==increament?toggle_y = -increament : toggle_y = increament;
                setbkcolor(LIGHTGREEN);
                setcolor(BLACK);
                BoundaryFill(prvs_circle.x,prvs_circle.y,GREEN,LIGHTGREEN);
                outtextxy(prvs_txt.x,prvs_txt.y,prvs_str);
                setbkcolor(LIGHTBLUE);
                BoundaryFill(-540,-140,GREEN,LIGHTBLUE);
                outtextxy(220,500,"U");
                prvs_circle = PT(-540,-140);
                prvs_txt = PT(220,500);
                prvs_str[0] = 'U';
            }
            drawPixel(tran[i].first,tran[i].second,1);
        }


    }

    counter_x += toggle_x;
    counter_y += toggle_y;
    return ;
}

#endif // TRANSITION_H_INCLUDED
