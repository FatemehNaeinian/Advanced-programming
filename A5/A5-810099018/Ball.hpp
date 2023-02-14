
#ifndef BALL_H
#define BALL_H "BALL_H"
#include "RSDL/src/rsdl.hpp"

class Ball{
public:
    void initialize(int x, int y);
    float ball_get_x();
    float ball_get_y();
    float ball_get_Vx();
    float ball_get_Vy();
    void update(Window& window);
    void draw(Window& window);
    void update_speed(Window&window,Point & click,Point &release);
    void update_speed_normalANDsand_area(float miu);
    void update_speed_wall(int ratiox , int ratioy);
private:
    float x;
    float y;
    float Vx;
    float Vy;
};
#endif