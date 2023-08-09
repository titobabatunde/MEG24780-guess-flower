//
//  demo.cpp
//  individualproject
//
//  Created by Tito Babatunde on 10/24/22.
//
/*
 Lecture 8-> Font Sample & Subsecond timer
 Things I want to do:
 Maximum of 60 seconds play
 Must stop when user presses ESC
 Must have audio and be able to import files
 
 (1) Increase shuffling from 1D to 2D
 (2) Show rocket ship landing on planet
 (3) Show gold cases walking out of ship
 (4) Then begin shuffling for the next 20-30 seconds
 */

/*
check to see what's under the box
 */

#include <stdio.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include <math.h>
#include <stdlib.h>
#include "yssimplesound.h"

void PhysicalCoordToScreenCoord(int &sx,int &sy,double px,double py)
{
    sx=(int)(px*10.0);
    sy=600-(int)(py*10.0);
}

void DrawPlant(double xp, double yp, double hh)
{
    const double TB_PI=3.1415927;
    
    glShadeModel(GL_SMOOTH);
    //glColor3f(0.89,0.45,0.39); //wood brown
    glBegin(GL_QUADS);
    glColor3ub(138,51,36);
    glVertex2d(xp-30.5,yp+hh);
    glColor3ub(166,123,91);
    glVertex2d(xp-40.5,yp+10.0);
    glColor3ub(75,54,33);
    glVertex2d(xp+40.5,yp+10.0);
    glColor3ub(210,105,30);
    glVertex2d(xp+30.5,yp+hh);
    glEnd();
    
    glShadeModel(GL_SMOOTH);
    //glColor3f(0.89,0.45,0.39); //wood brown
    glBegin(GL_QUADS);
    glColor3ub(138,51,36);
    glVertex2d(xp-hh,yp+10.0);
    glColor3ub(166,123,91);
    glVertex2d(xp-hh,yp);
    glColor3ub(75,54,33);
    glVertex2d(xp+hh,yp);
    glColor3ub(210,105,30);
    glVertex2d(xp+hh,yp+10.0);
    glEnd();
    
    glColor3f(0.0,0.0,0.0); //wood brown
    glBegin(GL_LINE_LOOP);
    glVertex2d(xp-30.5,yp+hh);
    glVertex2d(xp-40.5,yp+10.0);
    glVertex2d(xp-hh,yp+10.0);
    glVertex2d(xp-hh,yp);
    glVertex2d(xp+hh,yp);
    glVertex2d(xp+hh,yp+10.0);
    glVertex2d(xp+40.5,yp+10.0);
    glVertex2d(xp+30.5,yp+hh);
    glEnd();
    
    glColor3f(0.42,0.52,0.43);
    glBegin(GL_POLYGON);
    for(int i=0;i<360;i++)
    {
        double radians = (double)i*(TB_PI/180.0);
        double x = (hh-3.0)*sin(4.0*radians)*sin(radians)+xp;
        double y = (hh-3.0)*sin(4.0*radians)*cos(radians)+yp;
        glVertex2d(x,y);
    }
    glEnd();

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<360;i++)
    {
        double radians = (double)i*(TB_PI/180.0);
        double x = (hh-3.0)*sin(4.0*radians)*sin(radians)+xp;
        double y = (hh-3.0)*sin(4.0*radians)*cos(radians)+yp;
        glVertex2d(x,y);
    }
    glEnd();
}

void DrawBox(double xc, double yc, double hh)
{
    glShadeModel(GL_SMOOTH);
    glBegin(GL_POLYGON);
    glColor3ub(218,165,32);
    glVertex2d(xc-hh,yc+hh);
    glColor3ub(244,196,48);
    glVertex2d(xc-hh,yc-hh+10.0);
    glColor3ub(218,165,32);
    glVertex2d(xc-5.0,yc-hh+5.0);
    glColor3ub(244,196,48);
    glVertex2d(xc-5.0,yc-hh);
    glColor3ub(218,165,32);
    glVertex2d(xc+5.0,yc-hh);
    glColor3ub(244,196,48);
    glVertex2d(xc+5.0,yc-hh+5.0);
    glColor3ub(218,165,32);
    glVertex2d(xc+hh,yc-hh+10.0);
    glColor3ub(244,196,48);
    glVertex2d(xc+hh,yc+hh);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0,0.0,0.0);
    glVertex2d(xc-hh,yc+hh);
    glVertex2d(xc-hh,yc-hh+10.0);
    glVertex2d(xc-5.0,yc-hh+5.0);
    glVertex2d(xc-5.0,yc-hh);
    glVertex2d(xc+5.0,yc-hh);
    glVertex2d(xc+5.0,yc-hh+5.0);
    glVertex2d(xc+hh,yc-hh+10.0);
    glVertex2d(xc+hh,yc+hh);
    glEnd();
    
}

void DrawBeforeBoxOpen(void)
{
    glColor3ub(0,0,0);
    glRasterPos2d(100,80);
    //16x24, 16x20
    YsGlDrawFontBitmap16x24("Where do you think the plant is?");
}

void DrawBeforeBoxClose(void)
{
    glColor3ub(0,0,0);
    glRasterPos2d(100,80);
    YsGlDrawFontBitmap16x24("Help the plant get sunlight!");
}
void DrawBeforeBoxClose2(void)
{
    glColor3ub(0,0,0);
    glRasterPos2d(100,80);
    YsGlDrawFontBitmap16x24("Hmm, let's make this complicated.");
}

void DrawFirstScene(void)
{
    glColor3ub(0,0,0);
    glRasterPos2d(400,400);
    YsGlDrawFontBitmap16x24("Spaceship landed.");
}

void DrawSecondScene(void)
{
    glColor3ub(170,108,57);
    glRasterPos2d(400,400);
    YsGlDrawFontBitmap16x24("Gold containers invade");
    
    glColor3ub(170,108,57);
    glRasterPos2d(400,430);
    YsGlDrawFontBitmap16x24("plant planet.");
}

void DrawThirdScene(void)
{
    glColor3ub(1,50,32);
    glRasterPos2d(400,400);
    YsGlDrawFontBitmap16x24("Plants are saved!");
}

void DrawPlanet(double xp, double yp)
{
    const double TB_PI=3.1415927;
    double radius=60.0;
    //circle
    glShadeModel(GL_SMOOTH);
    glBegin(GL_POLYGON);
    for(int i=0;i<360;i++)
    {
        if (i%45==0)
        {
            glColor3ub(28,163,236);
        }
        else
        {
            glColor3ub(90,188,216);
        }
        double radians = (double)i*(TB_PI/180.0);
        double x = xp +(radius*cos(radians));
        double y = yp +(radius*sin(radians));
        glVertex2d(x,y);
    }
    glEnd();
    
    glColor3ub(0,0,0);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<360;i++)
    {
        double radians = (double)i*(TB_PI/180.0);
        double x = xp +(radius*cos(radians));
        double y = yp +(radius*sin(radians));
        glVertex2d(x,y);
    }
    glEnd();
    
    //flower
    glShadeModel(GL_SMOOTH);
    glBegin(GL_POLYGON);
    for(int i=0;i<360;i++)
    {
        if (i%30==0)
        {
            glColor3ub(37,82,59);
        }
        else if (i%45==0)
        {
            glColor3ub(53,136,86);
        }
        else
        {
            glColor3ub(98,189,105);
        }
        double radians = (double)i*(TB_PI/180.0);
        double x = (radius-3.0)*sin(4.0*radians)*sin(radians)+xp;
        double y = (radius-3.0)*sin(4.0*radians)*cos(radians)+yp;
        glVertex2d(x,y);
    }
    glEnd();

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<360;i++)
    {
        double radians = (double)i*(TB_PI/180.0);
        double x = (radius-3.0)*sin(4.0*radians)*sin(radians)+xp;
        double y = (radius-3.0)*sin(4.0*radians)*cos(radians)+yp;
        glVertex2d(x,y);
    }
    glEnd();
}

void DrawRocket(double px, double py, int landed)
{
    //Ship hat
    int xs,ys;
    PhysicalCoordToScreenCoord(xs,ys,px,py);
    glColor3ub(0,0,0);
    glBegin(GL_TRIANGLES);
    glVertex2i(xs,ys-40);
    glVertex2i(xs-20,ys-20);
    glVertex2i(xs+20,ys-20);
    glEnd();
    glColor3ub(0,0,0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(xs,ys-40);
    glVertex2i(xs-20,ys-20);
    glVertex2i(xs+20,ys-20);
    glEnd();
    
    //Ship body
    glColor3ub(102,51,153);
    glBegin(GL_QUADS);
    glVertex2i(xs-20,ys-20);
    glVertex2i(xs+20,ys-20);
    glVertex2i(xs+20,ys+40);
    glVertex2i(xs-20,ys+40);
    glEnd();
    glColor3ub(0,0,0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(xs-20,ys-20);
    glVertex2i(xs+20,ys-20);
    glVertex2i(xs+20,ys+40);
    glVertex2i(xs-20,ys+40);
    glEnd();
    
    //Window
    glShadeModel(GL_SMOOTH);
    glBegin(GL_POLYGON);
    const double TB_PI=3.1415927;
    for(int i=0;i<360;i++)
    {
        if (i%45==0)
        {
            glColor3ub(181,255,246);
        }
        else
        {
            glColor3ub(235,255,253);
        }
        double radians = (double)i*(TB_PI/180.0);
        double x = xs +(10.0*cos(radians));
        double y = ys +(10.0*sin(radians));
        glVertex2d(x,y);
    }
    glEnd();
    
    glColor3ub(0,0,0);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<360;i++)
    {
        double radians = (double)i*(TB_PI/180.0);
        double x = xs +(10.0*cos(radians));
        double y = ys +(10.0*sin(radians));
        glVertex2d(x,y);
    }
    glEnd();
    
    //Ship Fin1
    glColor3ub(121,6,4);
    glBegin(GL_TRIANGLES);
    glVertex2i(xs-20,ys);
    glVertex2i(xs-20,ys+40);
    glVertex2i(xs-40,ys+40);
    glEnd();
    glColor3ub(0,0,0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(xs-20,ys);
    glVertex2i(xs-20,ys+40);
    glVertex2i(xs-40,ys+40);
    glEnd();
    
    //ShipFin2
    glColor3ub(121,6,4);
    glBegin(GL_TRIANGLES);
    glVertex2i(xs+20,ys);
    glVertex2i(xs+20,ys+40);
    glVertex2i(xs+40,ys+40);
    glEnd();
    glColor3ub(0,0,0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(xs+20,ys);
    glVertex2i(xs+20,ys+40);
    glVertex2i(xs+40,ys+40);
    glEnd();
    
    if (landed==0)
    {
        //Fire
        glShadeModel(GL_SMOOTH);
        glBegin(GL_POLYGON);
        glColor3ub(255,168,54);
        glVertex2i(xs-20,ys+40);
        glColor3ub(245,118,26);
        glVertex2i(xs-40,ys+70);
        glColor3ub(245,118,26);
        glVertex2i(xs-20,ys+60);
        glColor3ub(226,99,16);
        glVertex2i(xs-20,ys+80);
        glColor3ub(255,168,54);
        glVertex2i(xs,ys+60);
        glColor3ub(255,168,54);
        glVertex2i(xs+20,ys+80);
        glColor3ub(245,118,26);
        glVertex2i(xs+20,ys+60);
        glColor3ub(245,118,26);
        glVertex2i(xs+40,ys+70);
        glColor3ub(255,168,54);
        glVertex2i(xs+20,ys+40);
        glEnd();
        glColor3ub(240,97,5);
        glBegin(GL_LINE_STRIP);
        glVertex2i(xs-20,ys+41);
        glVertex2i(xs-40,ys+70);
        glVertex2i(xs-20,ys+60);
        glVertex2i(xs-20,ys+80);
        glVertex2i(xs,ys+60);
        glVertex2i(xs+20,ys+80);
        glVertex2i(xs+20,ys+60);
        glVertex2i(xs+40,ys+70);
        glVertex2i(xs+20,ys+41);
        glEnd();
    }
    
}

void DrawFirstIntro(void)
{
    /*
     Maybe have a jungle thing run for five seconds
     */
}

void DrawSun(double xc, double yc, int state)
{
    const double TB_PI=3.1415927;
    double radius=40.0;
    int delta1;
    double plus1;
    if (state==0)
    {
        //30
        delta1=30;
        plus1=23.0;
    }
    else
    {
        delta1=15.0;
        plus1=23.0;
    }
    
    glColor3f(0.0,0.0,0.0);
    glLineWidth(3.0);
    glBegin(GL_LINES);
    for(int i=0;i<360;i+=delta1)
    {
        double radians = (double)i*(TB_PI/180.0);
        double x1 = xc +((radius+5.0)*cos(radians));
        double y1 = yc +((radius+5.0)*sin(radians));
        double x2 = xc +((radius+5.0+plus1)*cos(radians));
        double y2 = yc +((radius+5.0+plus1)*sin(radians));
        glVertex2d(x1,y1);
        glVertex2d(x2,y2);
    }
    glEnd();
    
    glColor3ub(249,215,28);
    glBegin(GL_POLYGON);
    for(int i=0;i<360;i++)
    {
        double radians = (double)i*(TB_PI/180.0);
        double x = xc +(radius*cos(radians));
        double y = yc +(radius*sin(radians));
        glVertex2d(x,y);
    }
    glEnd();

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<360;i++)
    {
        double radians = (double)i*(TB_PI/180.0);
        double x = xc +(radius*cos(radians));
        double y = yc +(radius*sin(radians));
        glVertex2d(x,y);
    }
    glEnd();
}

void DrawPlanetPlants(double xp, double yp)
{
    //flower
    const double TB_PI=3.1415927;
    double radius=50.0;
    glShadeModel(GL_SMOOTH);
    glBegin(GL_POLYGON);
    for(int i=0;i<360;i++)
    {
        if (i%30==0)
        {
            glColor3ub(37,82,59);
        }
        else if (i%45==0)
        {
            glColor3ub(53,136,86);
        }
        else
        {
            glColor3ub(98,189,105);
        }
        double radians = (double)i*(TB_PI/180.0);
        double x = (radius-3.0)*sin(4.0*radians)*sin(radians)+xp;
        double y = (radius-3.0)*sin(4.0*radians)*cos(radians)+yp;
        glVertex2d(x,y);
    }
    glEnd();

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<360;i++)
    {
        double radians = (double)i*(TB_PI/180.0);
        double x = (radius-3.0)*sin(4.0*radians)*sin(radians)+xp;
        double y = (radius-3.0)*sin(4.0*radians)*cos(radians)+yp;
        glVertex2d(x,y);
    }
    glEnd();
}

void DrawEnd(double xp,double yp, int won)
{
    const double TB_PI=3.1415927;
    double radius=60.0;
    if (won==1)
    {
        glColor3f(0.0,1.0,0.0);
    }
    else
    {
        glColor3f(1.0,0.0,0.0);
    }
    glBegin(GL_POLYGON);
    for(int i=0;i<360;i++)
    {
        double radians = (double)i*(TB_PI/180.0);
        double x = xp +(radius*cos(radians));
        double y = yp +(radius*sin(radians));
        glVertex2d(x,y);
    }
    glEnd();

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<360;i++)
    {
        double radians = (double)i*(TB_PI/180.0);
        double x = xp +(radius*cos(radians));
        double y = yp +(radius*sin(radians));
        glVertex2d(x,y);
    }
    glEnd();
    
    
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<360;i++)
    {
        double xx=xp+20.0;
        double yy=yp-(radius/2.0);
        double radians = (double)i*(TB_PI/180.0);
        double x = xx +(10.0*cos(radians));
        double y = yy +(10.0*sin(radians));
        glVertex2d(x,y);
    }
    glEnd();
    
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<360;i++)
    {
        double xx=xp-20.0;
        double yy=yp-(radius/2.0);
        double radians = (double)i*(TB_PI/180.0);
        double x = xx +(10.0*cos(radians));
        double y = yy +(10.0*sin(radians));
        glVertex2d(x,y);
    }
    glEnd();
    
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    if (won==1)
    {
        for(int i=0;i<180;i+=1)
        {
            double yy=yp+20.0;
            double radians = (double)i*(TB_PI/180.0);
            double x = xp +(30.0*cos(radians));
            double y = yy +(30.0*sin(radians));
            glVertex2d(x,y);
        }
    }
    else
    {
        for(int i=180;i<360;i+=1)
        {
            double yy=yp+20.0;
            double radians = (double)i*(TB_PI/180.0);
            double x = xp +(30.0*cos(radians));
            double y = yy +(30.0*sin(radians));
            glVertex2d(x,y);
        }
    }
    glEnd();
    
}

void SwapInt(int &a, int &b)
{
    int c;
    c=b;
    b=a;
    a=c;
}

void SwapDouble(double &a, double &b)
{
    double c;
    c=b;
    b=a;
    a=c;
}

void Shuffle(int x[],double X[],int size)
{
    for(int i=0;i<size;i++)
    {
        int r=rand()%size;
        if(r != i)
        {
            SwapInt(x[i],x[r]);
            SwapDouble(X[i],X[r]);
        }
    }
    
}

int Move(int x[],double X[],double xloc[], int size, double step)
{
    //int state[size];
    for (int i=0; i<size; ++i)
    {
        if (xloc[i]<X[i])//&& x[i]>i)
        {
            X[i]-=step;
            //state[i]=0;
            
        }
        else if (xloc[i]>X[i])//&& x[i]<i)
        {
            X[i]+=step;
            //state[i]=0;
        }
        else //if (xloc[i] == X[i])
        {
            //state[i]=1; //no need to move
        }
    }
    
    int flag=0;
    for (int i=0; i<size; ++i)
    {
        if (X[i]!=xloc[i])
        {
            flag=0;
            break;
        }
        else
        {
            flag=1;
        }
    }
    return flag;
}

int MoveBoxesInPlanet(double Xbox[], double Boxes[], int size, double step)
{
    for (int i=0; i<size; i++)
    {
        if (Xbox[i]!=Boxes[i])
        {
            Xbox[i]+=step;
        }
    }
    int flag=0;
    for (int i=0; i<size; i++)
    {
        if (Xbox[i]!=Boxes[i])
        {
            flag=0;
            break;
        }
        else
        {
            flag=1;
        }
    }
    return flag;
}

void MoveRocket(double &xShip, double &yShip, double &VxShip, double &VyShip)
{
    double m=1.0;
    double dt=0.02;
    
    xShip+=VxShip*dt;
    yShip+=VyShip*dt;
    VyShip-=9.8*dt;
    //printf("Ship=%1f,%1f\n",xShip,yShip);
}

int CheckHitPlanet(double xPlanet, double yPlanet, double xShip, double yShip)
{
    double shipH=40.0;
    double planetH=60.0;
    int relativeX,relativeY;
    int xxShip, yyShip;
    PhysicalCoordToScreenCoord(xxShip, yyShip, xShip, yShip);
    yyShip+=shipH;
    xPlanet-=planetH;
    yPlanet-=planetH;
    relativeX=xxShip-xPlanet;
    relativeY=yyShip-yPlanet;
    if(0<=relativeX && relativeX<(2*planetH) && 0<=relativeY && relativeY<(2*planetH))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int CheckShuffle(double X[], double xloc[], int size)
{
    int flag=0;
    for (int i=0; i<size; ++i)
    {
        if (X[i]!=xloc[i])
        {
            flag=0;
            break;
        }
        else
        {
            flag=1;
        }
    }
    return flag;
}

void OpenBox(double X[], double Y[], int boxn, double step, double hh, double ystart)
{
    double maxHeight=(ystart-(hh*2.0));
    //printf("%1f\n",maxHeight);
    //for (int i=0; i<size; ++i)
    //{
    if(Y[boxn]>maxHeight)
    {
        Y[boxn]-=step;
    }
    //}
    //printf("%1f,%1f,%1f\n",Y[0],Y[1],Y[2]);
}

int CloseBox(double Y[], int size, double step, double ystart)
{
    //int state[size];
    for (int i=0; i<size; ++i)
    {
        double moved=Y[i]+step;
        if(moved<=ystart)
        {
            Y[i]=moved;
        }
    }

    if (Y[0]==ystart && Y[1]==ystart && Y[2]==ystart)
    {
        //printf("%1f,%1f,%1f,%d\n",X[0],X[1],X[2],1);
        return 1;
        
    }
    else
    {
        return 0;
    }
    //if 1 then ready to start moving
}


//so we will open each glass
//first have three glasses then we'll have five glasses

int main(void)
{
    // xp=xplant, yp=yplant, hh=halfheight
    double hh=50.0; //meters
    const double TB_PI=3.1415927;
    int plantindex=1;
    int idx=0;
    double xstart[3]={240.0,150.0,80.0},ystart[3]={300.0,300.0,300.0};
    double xShip=15.0,yShip=9.0;
    double xxShip=100.0, yyShip=510.0;
    double angle=80.0*(TB_PI/180.0);
    double VxShip=32.0*cos(angle);
    double VyShip=32.0*sin(angle);
    int landed=0;
    double xPlanet=400.0;
    double yPlanet=183.0;
    
    double step=10.0; //20.0
    int scrnSizeX=800, scrnSizeY=600;
    int shufflecount=15; //houw long to shuffle
    static const int size[3]={3,4,5};
    int timecounter=0; //has the button been pressed?
    int sun=1;
    int sunstate=0;
    double xsun=700.0,ysun=70.0;
    double xPlants[16], yPlants[16];
    double xPlant=0.0, yPlant=590.0;
    double Xbox[]={xxShip,xxShip,xxShip,xxShip};
    double Ybox[]={yyShip,yyShip,yyShip,yyShip};
    double Boxes[]={180,350,550,750};
    int finalPlanet=0;
    int clip1=0, clip2=0, clip3=0;
    
    for (int i=0; i<17; i++)
    {
        if (i%2==0)
        {
            yPlants[i]=yPlant;
        }
        else
        {
            yPlants[i]=yPlant-20.0;
        }
        xPlants[i]=xPlant;
        xPlant+=50.0;
        printf("%d=%1f,%1f\n",i,xPlants[i],yPlants[i]);
    }
    
    FsChangeToProgramDir();
    
    YsSoundPlayer background;
    YsSoundPlayer rocketlanding;
    YsSoundPlayer shuffling;
    YsSoundPlayer rocketflying;
    
    YsSoundPlayer::SoundData wavbackground;
    YsSoundPlayer::SoundData wavlanding;
    YsSoundPlayer::SoundData wavflying;
    YsSoundPlayer::SoundData wavshuffling;
    
    if(YSOK == wavbackground.LoadWav("background.wav"))
    {
        background.Start();
    }
    //background.PlayOneShot(wavbackground);
    if(YSOK == wavlanding.LoadWav("rocketlanding.wav"))
    {
        rocketlanding.Start();
    }
    if(YSOK == wavflying.LoadWav("longswoosh.wav"))
    {
        rocketflying.Start();
    }
    
    background.PlayBackground(wavbackground);
    //initializes
    /*
     int x[size[idx]];
     double xloc[size[idx]];
     double X[size[idx]];
     double Y[size[idx]];
     */
    int click=0; //user can click? (no=0),(yes=1)
    int boxn=0;
    int move=0; //can shuffling begin? (no=0),(yes=1)
    int count=0;
    int shuffle=0; //can I shuffle? (no=0), (yes=1)
    int check=0;
    //starting locations for emptybox, emptybox+plant,emptybox
    double xloc[5]={-1,-1,-1,-1,-1};
    double X[5]={-1,-1,-1,-1,-1};
    double Y[5]={-1,-1,-1,-1,-1};
    int x[5]={-1,-1,-1,-1,-1};
    //FsPassedTime(); //Dummy call to reset the sub-second timer
    unsigned int passed=0;
    
    int open[3][5]={{3,1,2,0,0},{4,1,3,2,0},{1,4,5,3,2}}; //which box will open
    int won;
    for (int i=0; i<size[idx];++i)
    {
        x[i]=i;
    }
    //setting up location per x index
    //printf("%1f\n",ystart[idx]-(hh*2.0));
    for (int i=0; i<size[idx]; ++i)
    {
        xloc[i]=xstart[idx]+(160.0*i);
        X[i]=xstart[idx]+(160.0*i);
        Y[i]=ystart[idx]-(hh*2.0); //all starting open
    }
    
    FsOpenWindow(16,16,scrnSizeX,scrnSizeY,1);
    
    FsPollDevice();
    //for (;;)
    while(FSKEY_ESC!=FsInkey())
    {
        FsPollDevice();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        sun++;
        if (sun%5==0)
        {
            sunstate=0;
        }
        else
        {
            sunstate=1;
        }
        landed=CheckHitPlanet(xPlanet, yPlanet, xShip, yShip);
        if (landed==0)
        {
            MoveRocket(xShip,yShip,VxShip,VyShip);
        }
        
        DrawFirstScene();
        DrawSecondScene();
        DrawThirdScene();
        DrawRocket(xShip, yShip, landed);
        DrawSun(xsun,ysun,sunstate);
        DrawPlanet(xPlanet,yPlanet);
        for (int i=0; i<17; i++)
        {
            DrawPlanetPlants(xPlants[i], yPlants[i]);
        }
        finalPlanet=MoveBoxesInPlanet(Xbox, Boxes, 4, step);
        for (int i=0; i<4; i++)
        {
            DrawBox(Xbox[i], Ybox[i], 30.0);
        }
        DrawRocket(xxShip/10,(600-yyShip)/10,1);
        
        //printf("%d,%d,%d\n",lb,mx,my);
        if (move==0)
        {
            //printf("%d\n",passed);
            if (idx==0)
            {
                DrawBeforeBoxClose();
            }
            else
            {
                DrawBeforeBoxClose2();
            }
            if (timecounter==0)
            {
                FsPassedTime();
                passed=0;//reset
            }
            passed+=FsPassedTime();
            if (passed < 2000)
            {
                timecounter++;
            }
            else
            {
                move=CloseBox(Y, size[idx], step, ystart[idx]);
                if (move==1)
                {
                    shuffle=1;
                    timecounter=0;
                    //passed=0;
                }
            }
            /*
            if (idx==1)
            {
                printf("Check box is closing...\n");
                printf("x=[%d,%d,%d,%d,%d]\n",x[0],x[1],x[2],x[3],x[4]);
                printf("X=[%1f,%1f,%1f,%1f,%1f]\n",X[0],X[1],X[2],X[3],X[4]);
                printf("Y=[%1f,%1f,%1f,%1f,%1f]\n",Y[0],Y[1],Y[2],Y[3],Y[4]);
            }*/
            DrawPlant(X[plantindex],ystart[idx],hh);
            
            for (int i=0;i<size[idx];++i)
            {
                DrawBox(X[i], Y[i], hh);
            }
        }
        
        if (move==1 && shuffle==1 && click==0)
        {
            if(count < shufflecount)
            {
                Shuffle(x,X,size[idx]);
                count+=1;
                shuffle=0;
            }
            else
            {
                for (int i=0;i<size[idx];++i)
                {
                    DrawBox(X[i], Y[i], hh);
                }
                DrawBeforeBoxOpen();
                if (timecounter==0)
                {
                    FsPassedTime();
                    passed=0;//reset
                }
                passed+=FsPassedTime();
                //printf("seconds=%d\n",passed);
                if (passed < 5000)
                {
                    timecounter++;
                }
                else
                {
                    click=CheckShuffle(X, xloc, size[idx]);
                    timecounter=0;
                    printf("x=[%d,%d,%d,%d,%d]\n",x[0],x[1],x[2],x[3],x[4]);
                    printf("X=[%1f,%1f,%1f,%1f,%1f]\n",X[0],X[1],X[2],X[3],X[4]);
                    printf("Y=[%1f,%1f,%1f,%1f,%1f]\n",Y[0],Y[1],Y[2],Y[3],Y[4]);
                }
                /*if (timecounter<30)
                {
                    timecounter++;
                    passed=FsPassedTime();
                    printf("seconds=%d\n",passed);
                    //here we print "wanna take a guess?"
                }*/

            }
            //printf("count=%d\n",count);
            //printf("%1f,%1f,%1f\n",X[0],X[1],X[2]);
        }
        else //(move==1 && shuffle==0 && click==0)
        {
            shuffle=Move(x,X,xloc,size[idx],step);
            //printf("%1f,%1f,%1f\n",X[0],X[1],X[2]);
            for (int i=0;i<size[idx];++i)
            {
                DrawBox(X[i], Y[i], hh);
            }
            if (shuffle==1 && count==shufflecount)
            {
                //click=CheckShuffle(X, xloc, size[idx]);
            }
            //printf("shuffle=%d,move=%d,count=%d,click=%d\n",shuffle,move,count,click);
        }
        //printf("%d\n",click);
        if (click==1)
        {
            //printf("x=[%d,%d,%d,%d,%d], open[%d]=%d\n",x[0],x[1],x[2],x[3],x[4],boxn,open[idx][boxn]-1);
            //printf("X=[%1f,%1f,%1f,%1f,%1f], %1f\n",X[0],X[1],X[2],X[3],X[4],X[open[idx][boxn]-1]);
            for(int i=0;i<size[idx];++i)
            {
                if(x[i]==plantindex)
                {
                    DrawPlant(X[i], ystart[idx], hh);
                }
                DrawBox(X[i], Y[i], hh);
                
                if (open[idx][boxn]-1==x[i])
                {
                    OpenBox(X, Y, i, step, hh, ystart[idx]);
                }
            }//end-for
            // if the box is fully lifted &&
            // what you pressed is not where the plant is
            for (int k=0; k<=boxn; k++)
            {
                for (int i=0; i<size[idx]; ++i)
                {
                    if (open[idx][k]-1==x[i])
                    {
                        if (Y[i]==ystart[idx]-(hh*2.0) && x[i]!=plantindex)
                        {
                            won=0;
                            DrawEnd(X[i],Y[i],won);
                        }
                        else if (Y[i]==ystart[idx]-(hh*2.0) && x[i]==plantindex)
                        {
                            won=1;
                            DrawEnd(X[i],Y[i],won);
                        }
                    }
                }
            }
                
            for (int i=0; i<size[idx]; ++i)
            {
                if (open[idx][boxn]-1==x[i])
                {
                    if (Y[i]==ystart[idx]-(hh*2.0) && x[i]!=plantindex)
                    {
                        //break;
                        boxn++;
                    }
                }
            }
            
            //if at the end and reached plant index
            if (Y[size[idx]-1]==ystart[idx]-(hh*2.0) && boxn == size[idx]-1)
            {
                if (timecounter < 40)
                {
                    timecounter++;
                }
                else
                {
                    //RESET
                    if (idx<2)
                    {
                        idx++;
                    }
                    //initializes
                    click=0; //user can click? (no=0),(yes=1)
                    boxn=0;
                    move=0; //can shuffling begin? (no=0),(yes=1)
                    count=0;
                    shuffle=0; //can I shuffle? (no=0), (yes=1)
                    timecounter=0;
                    check=0;
                    passed=0;
                    //starting locations for emptybox, emptybox+plant,emptybox
                    for (int i=0; i<size[idx];++i)
                    {
                        x[i]=i;
                    }
                    //setting up location per x index
                    //printf("%1f\n",ystart[idx]);
                    for (int i=0; i<size[idx]; ++i)
                    {
                        xloc[i]=xstart[idx]+(160.0*i);
                        X[i]=xstart[idx]+(160.0*i);
                        Y[i]=ystart[idx]-(hh*2.0); //all starting open
                    }
                    printf("x=[%d,%d,%d,%d,%d]\n",x[0],x[1],x[2],x[3],x[4]);
                    printf("X=[%1f,%1f,%1f,%1f,%1f]\n",X[0],X[1],X[2],X[3],X[4]);
                    printf("Y=[%1f,%1f,%1f,%1f,%1f]\n",Y[0],Y[1],Y[2],Y[3],Y[4]);
                    printf("RESET");
                }
            }
        }
        
            
            //printf("%d %d %d %d %d\n",lb,mb,rb,mx,my);
        //}
        

        FsSwapBuffers();
        FsSleep(30);
        
    }
    background.End();
    
    return 0;

}

/*
 const double TB_PI=3.1415927;
 
 glColor3f(0.89,0.45,0.39); //wood brown
 glBegin(GL_POLYGON);
 glVertex2d((xp-1.5)*10.0,(double)scrnSizeY-((yp-hh)*10.0));
 glVertex2d((xp-2.5)*10.0,(double)scrnSizeY-((yp-1.0)*10.0));
 glVertex2d((xp-hh)*10.0,(double)scrnSizeY-((yp-1.0)*10.0));
 glVertex2d((xp-hh)*10.0,(double)scrnSizeY-(yp*10.0));
 glVertex2d((xp+hh)*10.0,(double)scrnSizeY-(yp*10.0));
 glVertex2d((xp+hh)*10.0,(double)scrnSizeY-((yp-1.0)*10.0));
 glVertex2d((xp+2.5)*10.0,(double)scrnSizeY-((yp-1.0)*10.0));
 glVertex2d((xp+1.5)*10.0,(double)scrnSizeY-((yp-hh)*10.0));
 glEnd();
 
 glColor3f(0.0,0.0,0.0); //wood brown
 glBegin(GL_LINE_LOOP);
 glVertex2d((xp-1.5)*10.0,(double)scrnSizeY-((yp-hh)*10.0));
 glVertex2d((xp-2.5)*10.0,(double)scrnSizeY-((yp-1.0)*10.0));
 glVertex2d((xp-hh)*10.0,(double)scrnSizeY-((yp-1.0)*10.0));
 glVertex2d((xp-hh)*10.0,(double)scrnSizeY-(yp*10.0));
 glVertex2d((xp+hh)*10.0,(double)scrnSizeY-(yp*10.0));
 glVertex2d((xp+hh)*10.0,(double)scrnSizeY-((yp-1.0)*10.0));
 glVertex2d((xp+2.5)*10.0,(double)scrnSizeY-((yp-1.0)*10.0));
 glVertex2d((xp+1.5)*10.0,(double)scrnSizeY-((yp-hh)*10.0));
 glEnd();
 
 glColor3f(0.42,0.52,0.43);
 glBegin(GL_POLYGON);
 for(int i=0;i<360;i++)
 {
     double radians = (double)i*(TB_PI/180.0);
     double x = hh*sin(4.0*radians)*sin(radians)+xp;
     double y = hh*sin(4.0*radians)*cos(radians)+yp;
     glVertex2d(x*10.0,(double)scrnSizeY-(y*10.0));
 }
 glEnd();

 glColor3f(0.0,0.0,0.0);
 glBegin(GL_LINE_LOOP);
 for(int i=0;i<360;i++)
 {
     double radians = (double)i*(TB_PI/180.0);
     double x = hh*sin(4.0*radians)*sin(radians)+xp;
     double y = hh*sin(4.0*radians)*cos(radians)+yp;
     glVertex2d(x*10.0,(double)scrnSizeY-(y*10.0));
 }
 glEnd();
 */

