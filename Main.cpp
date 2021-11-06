
#include<bits/stdc++.h>
#include<windows.h>
#include<graphics.h>


using namespace std;

const int WINDOW_W = 1500, WINDOW_H = 700;
#define INF 10000
int counter_x = 0;
int counter_y = 0;
int toggle_x = 0;
int toggle_y = 0;

int FILL_COLOR=BROWN;
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
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

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
bool isInsideCircle(int circle_x, int circle_y,
                   int rad, int x, int y)
{

    if ((x - circle_x) * (x - circle_x) +
        (y - circle_y) * (y - circle_y) <= rad * rad)
        return true;
    else
        return false;
}
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

    PT prvs_circle = PT(-600,-200);
    PT prvs_txt = PT(160,560);

    char prvs_str[] = "L";


    while(1)
    {

        POINT pointt;
        if(GetCursorPos(&pointt))
        {
            ScreenToClient(GetForegroundWindow(), &pointt);
            int n = poly.size();
            PT cp = PT(pointt.x, pointt.y);
            PT ans= convertPixel(cp);
            PT p = {(int)ans.x-WINDOW_W, (int)ans.y};
            int dd=0;
            if(isInsideCircle(-600,-200,30,p.x,p.y) && GetAsyncKeyState(VK_LBUTTON))
            {
                toggle_x = -3;
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
                toggle_x = 3;
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
                cout << p.x << " hmm " << p.y << endl;
            }
            else if(isInsideCircle(-540,-140,30,p.x,p.y)&& GetAsyncKeyState(VK_LBUTTON))
            {
                toggle_y = 3;
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
                toggle_y = -3;
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
                printf("YES\n");
                cout<<p.x<<" "<<p.y<<endl;
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
