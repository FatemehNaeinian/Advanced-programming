
#include "RSDL/src/rsdl.hpp"
#include "playground.hpp"
#include "Ball.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define RADUIS_HOLE 18
void Playground::add_wall(Rectangle rectangle){
    walls.push_back(rectangle);
}

void Playground::add_water_area(Rectangle rectangle){
    waterArea.push_back(rectangle);
}

void Playground::add_normal_area(Rectangle rectangle){
    normalArea.push_back(rectangle);
}

void Playground::add_sand_area(Rectangle rectangle){
    sandArea.push_back(rectangle);
}

void Playground::add_sharp_wall(Rectangle rectangle){
    sharpWalls.push_back(rectangle);
}

void Playground::add_hole(Point hole_){
    hole=hole_;
}

void Playground::draw(Window& window){
    
    for(int i=0;i<normalArea.size();i++){
        window.draw_rect(normalArea[i],{51 , 102 ,0});
        window.fill_rect(normalArea[i],{51 , 102 ,0});
    }
    for(int i=0;i<waterArea.size();i++){
        window.draw_rect(waterArea[i],{51 ,151 ,215});
        window.fill_rect(waterArea[i],{51 ,151 ,215});
    }
    for(int i=0;i<sandArea.size();i++){
        window.draw_rect(sandArea[i],{102 ,51 ,0});
        window.fill_rect(sandArea[i],{102 ,51 ,0});
    }
    for(int i=0;i<walls.size();i++){
        window.draw_rect(walls[i],{255,153,51});
        window.fill_rect(walls[i],{255,153,51});
    }
    for(int i=0;i<sharpWalls.size();i++){
        window.draw_rect(sharpWalls[i],{80 , 25 ,0});
        window.fill_rect(sharpWalls[i],{80 , 25 ,0});
    }
    window.fill_circle(hole,RADUIS_HOLE ,BLACK);
}


void Playground::check(Window& window,Ball& ball,string &game){
    if(walls_check(ball)){
        if(which_wall(ball)==1){
            ball.update_speed_wall(1,-1);
        }
        if(which_wall(ball)==2){
            ball.update_speed_wall(-1,1);
        }
    }
    if(normal_area_check(ball)){
        if((int)ball.ball_get_Vx()==0 && (int)ball.ball_get_Vy()==0){
            ball.update_speed_normalANDsand_area(0);
        }
        else{
            ball.update_speed_normalANDsand_area(miu);
        }
    }
    if(sand_area_check(ball)){
        if((int)ball.ball_get_Vx()==0 && (int)ball.ball_get_Vy()==0){
            ball.update_speed_normalANDsand_area(0);
        }
        else{
            ball.update_speed_normalANDsand_area(0.9*miu);
        }
    }
    if(water_check(ball)){
        game="GAME OVER";
    }
    if(sharp_check(ball)){
        game="GAME OVER";
    }
    if(hole_check(ball)){
        game="WIN";
    }
}

bool Playground::hole_check(Ball& ball){
    int d =pow((pow(ball.ball_get_x()-hole.x,2))+pow(ball.ball_get_y()-hole.y,2),0.5);
    if(d < RADUIS_HOLE ){
        return true;
    }
    return false;
}

bool Playground::sharp_check(Ball& ball){
    for(int i=0 ; i<sharpWalls.size() ;i++){
        if((ball.ball_get_x()> (float)sharpWalls[i].x) && (ball.ball_get_y()> (float)sharpWalls[i].y) &&
            (ball.ball_get_x()< (float)(sharpWalls[i].x + sharpWalls[i].w))&&(ball.ball_get_y()< (float)(sharpWalls[i].y + sharpWalls[i].h))){
            return true;
        }
    }
    return false;
}

bool Playground::water_check(Ball& ball){
    for(int i=0 ; i<waterArea.size() ;i++){
        if((ball.ball_get_x()> (float)waterArea[i].x) && (ball.ball_get_y()> (float)waterArea[i].y) &&
            (ball.ball_get_x()< (float)(waterArea[i].x + waterArea[i].w))&&(ball.ball_get_y()< (float)(waterArea[i].y + waterArea[i].h))){
            return true;
        }
    }
    return false;
}

bool Playground::walls_check(Ball& ball){
    for(int i=0 ; i<walls.size() ;i++){
        if((ball.ball_get_x()> (float)walls[i].x) && (ball.ball_get_y()> (float)walls[i].y) &&
            (ball.ball_get_x()< (float)(walls[i].x + walls[i].w))&&(ball.ball_get_y()< (float)(walls[i].y + walls[i].h))){
            return true;
        }
    }
    return false;
}

bool Playground::normal_area_check(Ball& ball){
    for(int i=0 ; i<normalArea.size() ;i++){
        if((ball.ball_get_x()> (float)normalArea[i].x) && (ball.ball_get_y()> (float)normalArea[i].y) &&
            (ball.ball_get_x()< (float)(normalArea[i].x + normalArea[i].w))&&(ball.ball_get_y()< (float)(normalArea[i].y + normalArea[i].h))){
            return true;
        }
    }
    return false;
}

bool Playground::sand_area_check(Ball& ball){
    for(int i=0 ; i<sandArea.size() ;i++){
        if((ball.ball_get_x()> (float)sandArea[i].x) && (ball.ball_get_y()> (float)sandArea[i].y) &&
            (ball.ball_get_x()< (float)(sandArea[i].x + sandArea[i].w))&&(ball.ball_get_y()< (float)(sandArea[i].y + sandArea[i].h))){
            return true;
        }
    }
    return false;
}

int Playground::which_wall(Ball& ball){
    for(int i=0 ; i<walls.size() ;i++){
        if((ball.ball_get_x()> (float)walls[i].x) && (ball.ball_get_y()> (float)walls[i].y) &&
            (ball.ball_get_x()< (float)(walls[i].x + walls[i].w))&&(ball.ball_get_y()< (float)(walls[i].y + walls[i].h))){
            if(walls[i].w >walls[i].h){
                return 1;
            }
            else{
                return 2;
            }
        }
    }
    return 0;
}