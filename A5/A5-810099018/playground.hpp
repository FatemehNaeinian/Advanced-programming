
#ifndef PLAY_H
#define PLAY_H "PLAY_H"
#include "RSDL/src/rsdl.hpp"
#include "Ball.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Playground{
public:
    void add_wall(Rectangle rectangle);
    void add_water_area(Rectangle rectangle);
    void add_normal_area(Rectangle rectangle);
    void add_sand_area(Rectangle rectangle);
    void add_sharp_wall(Rectangle rectangle);
    void add_hole(Point hole);
    void draw(Window& window);
    void check(Window& window,Ball& ball,string &game);
    bool walls_check(Ball& ball);
    bool normal_area_check(Ball& ball);
    bool sand_area_check(Ball& ball);
    int which_wall(Ball& ball);
    bool water_check(Ball& ball);
    bool sharp_check(Ball& ball);
    bool hole_check(Ball& ball);
private:
    vector<Rectangle> walls;
    vector<Rectangle> sharpWalls;
    vector<Rectangle> waterArea;
    vector<Rectangle> normalArea;
    vector<Rectangle> sandArea;
    Point hole;
    float miu =0.98;
};
#endif