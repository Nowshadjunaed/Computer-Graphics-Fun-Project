#include<bits/stdc++.h>
#include<windows.h>
#include<graphics.h>
#include "Circle.h"
#include "Main.h"
#include "Polygon Filling.h"
#include "Circle Filling.h"
#include "Polygon.h"
#include "Line.h"
#include "Transition.h"

using namespace std;

int main()
{
    initwindow(WINDOW_W, WINDOW_H);

    vector<PT> poly;

    poly.push_back(PT(-140, -40));
    poly.push_back(PT(-90, -60));
    poly.push_back(PT(-40, -40));
    poly.push_back(PT(-40, 30));
    poly.push_back(PT(-90, 50));
    poly.push_back(PT(-140, 30));

    settextstyle(10,4,1);
    setbkcolor(BLACK);
    setcolor(WHITE);

    outtextxy(260,250,"To fill the object:");
    outtextxy(350,275,"click inside the object");
    outtextxy(260,300,"To move the object:");
    outtextxy(360,325, "to the RIGHT click on R,");
    outtextxy(350,345, "to the LEFT click on L,");
    outtextxy(350,365, "to the DOWN click on D,");
    outtextxy(317,385, "to the UP click on U");
    outtextxy(350,410, "To PAUSE moving click on P,");
    settextstyle(4,4,1);
    setbkcolor(LIGHTGREEN);
    setcolor(BLACK);

    Bressenham(30,-600,-200,GREEN);
    BoundaryFill(-600,-200,GREEN,LIGHTGREEN);
    outtextxy(160,560,"L");



    Bressenham(30,-480,-200,GREEN);
    BoundaryFill(-480,-200,GREEN,LIGHTGREEN);
    outtextxy(280,560,"R");

    Bressenham(30,-540,-140,GREEN);
    BoundaryFill(-540,-140,GREEN,LIGHTGREEN);
    outtextxy(220,500,"U");

    Bressenham(30,-540,-260,GREEN);
    BoundaryFill(-540,-260,GREEN,LIGHTGREEN);
    outtextxy(220,620,"D");

    settextstyle(3,4,1);
    setbkcolor(RED);
    setcolor(WHITE);

    Bressenham(15,-540,-200,GREEN);
    BoundaryFill(-540,-200,GREEN,RED);
    outtextxy(215,560,"P");

    drawPolygon(poly,WHITE);


    settextstyle(4,4,1);
    setbkcolor(LIGHTGREEN);
    setcolor(BLACK);




    while(1)
    {

        POINT pointt;
        if(GetCursorPos(&pointt))
        {
            ScreenToClient(GetForegroundWindow(), &pointt);
            int n = poly.size();
            PT pnt = convertPixel(PT(pointt.x, pointt.y));
            PT p = {(int)pnt.x-WINDOW_W, (int)pnt.y};
            if(isInsideCircle(-600,-200,30,p.x,p.y) && GetAsyncKeyState(VK_LBUTTON))
            {
                toggle_x = -increament;
                toggle_y = 0;

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

            else if(isInsideCircle(-480,-200,30,p.x,p.y) && GetAsyncKeyState(VK_LBUTTON))
            {
                toggle_x = increament;
                toggle_y=0;

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
            else if(isInsideCircle(-540,-140,30,p.x,p.y)&& GetAsyncKeyState(VK_LBUTTON))
            {
                toggle_y = increament;
                toggle_x=0;

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
            else if(isInsideCircle(-540,-260,30,p.x,p.y)&& GetAsyncKeyState(VK_LBUTTON))
            {
                toggle_y = -increament;
                toggle_x=0;


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
            else if(isInsideCircle(-540,-200,15,p.x,p.y)&& GetAsyncKeyState(VK_LBUTTON))
            {

                toggle_x = 0;
                toggle_y = 0;
                setbkcolor(LIGHTGREEN);
                setcolor(BLACK);
                BoundaryFill(prvs_circle.x,prvs_circle.y,GREEN,LIGHTGREEN);
                outtextxy(prvs_txt.x,prvs_txt.y,prvs_str);
                setbkcolor(LIGHTBLUE);
            }

            if(isInside(poly, n, p) && GetAsyncKeyState(VK_LBUTTON))
            {
                if(FILL_COLOR==CYAN) FILL_COLOR = BROWN;
                else FILL_COLOR = CYAN;
                scanLine(poly,FILL_COLOR);
            }

            Make_Transition();

        }
    }
    getch();
    return 0;
}
