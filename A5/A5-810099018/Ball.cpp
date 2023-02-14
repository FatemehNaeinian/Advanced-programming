#include "Ball.hpp"
#include "RSDL/src/rsdl.hpp"
#include <cmath>
#include <iostream>
#define THROWRADIUS 100
#define MAXSPEED 100
using namespace std;
#define SPEEDPERMS 25
void Ball::initialize(int x_, int y_){
    x=x_;
    y=y_;
    Vx=0;
    Vy=0;
}

float Ball::ball_get_x(){return x;}
float Ball::ball_get_y(){return y;}
float Ball::ball_get_Vy(){return Vy;}
float Ball::ball_get_Vx(){return Vx;}
void Ball::update(Window& window){
    x=x+Vx/SPEEDPERMS ;
    y=y+Vy/SPEEDPERMS ;
}
void Ball::draw(Window& window){
    window.fill_circle(Point(x,y),10);
}
void Ball::update_speed(Window&window,Point & click,Point &release){
    float d2=pow((click.x - release.x),2) + pow((click.y - release.y),2);
    float d=pow(d2,0.5);
    Point Fasele=Point((click.x - release.x), (click.y - release.y));
    if(d < THROWRADIUS){
        Vx= (float)MAXSPEED/(float)THROWRADIUS * (float)Fasele.x ;
        Vy= (float)MAXSPEED/(float)THROWRADIUS * (float)Fasele.y ;
    }
    if(d > THROWRADIUS){
        Vx= (float)MAXSPEED/d * (float)Fasele.x ;
        Vy= (float)MAXSPEED/d * (float)Fasele.y ;
    }
}
void Ball::update_speed_normalANDsand_area(float miu){
    Vx=miu * Vx;
    Vy=miu * Vy;
}
void Ball::update_speed_wall(int ratiox , int ratioy){
    Vx=Vx * ratiox;
    Vy=Vy * ratioy;
}