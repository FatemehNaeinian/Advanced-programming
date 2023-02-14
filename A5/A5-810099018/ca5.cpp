#include "RSDL/src/rsdl.hpp"
#include "readinput.hpp"
#include "playground.hpp"
#include "Ball.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define BALL_RADUIS 20
void read_input(string filename,Ball& ball,vector<int>&window_size,Playground &playgrounds){
    vector<string>fileToString= read_file(filename);
    apply_input_ball(fileToString,ball);
    apply_input_window(fileToString,window_size);
    apply_input_playground(fileToString,playgrounds);
}

void update(Window& window,Ball& ball,Point &mousePosition,Playground &playgrounds,Point &click,Point &release,int &is_clicked,string &game,int& NumOfShots){
    while(window.has_pending_event()){
        Event e = window.poll_for_event();
        switch (e.get_type()){
            case Event::EventType::QUIT:
                exit(0);
                break;
            case Event::EventType::MMOTION:
                mousePosition = e.get_mouse_position();
                break;
            case Event::EventType::LCLICK:
                click = e.get_mouse_position();
                is_clicked = 1;
                break;
            case Event::EventType::LRELEASE:
                release = e.get_mouse_position();
                is_clicked = 0;
                if(pow((pow(ball.ball_get_x()-click.x,2))+pow(ball.ball_get_y()-click.y,2),0.5)<BALL_RADUIS){
                    ball.update_speed(window,click,release);
                    NumOfShots++;
                }
                break;
        }
    }
    if(game=="ongoing"){
        playgrounds.check(window ,ball,game);
        ball.update(window);
    }
}

void draw(Window& window,Ball& ball,Point &mousePosition,Playground &playgrounds,Point &click,Point &release,int &is_clicked,string &game,int& NumOfShots){
    if(game=="ongoing"){
        window.clear();
        playgrounds.draw(window);
        ball.draw(window);
        if(is_clicked==1&&(pow((pow(ball.ball_get_x()-click.x,2))+pow(ball.ball_get_y()-click.y,2),0.5)<BALL_RADUIS)){
            window.draw_line(click , mousePosition , BLACK);
        }    
        stringstream shots;
        shots << "shots = "<< NumOfShots;
        string text = shots.str();
        window.show_text(text ,{11,9} , BLACK ,"RSDL/example/assets/OpenSans.ttf",20);
    }
    if(game=="GAME OVER"){
        window.draw_rect(Rectangle(180,180,300,100),{0,0,0});
        window.fill_rect(Rectangle(180,180,300,100),{255,51,51});
        window.show_text(game ,{200,200} , WHITE ,"RSDL/example/assets/OpenSans.ttf",40);
    }
    if(game=="WIN"){
        window.draw_rect(Rectangle(220,180,150,100),{0,0,0});
        window.fill_rect(Rectangle(220,180,150,100),{153,0,76});
        window.show_text(game ,{250 ,200} , WHITE ,"RSDL/example/assets/OpenSans.ttf",40);
    }
    window.update_screen();   
}

int main(int argc, char* argv[]){
    vector<int>window_size;
    Point mousePosition;
    Point click;
    Point release;
    Ball ball;
    int is_clicked=0;
    Playground playgrounds;
    string filename=argv[1];
    string game="ongoing";
    int NumOfShots=0;
    read_input(filename,ball,window_size,playgrounds);
    Window window=Window(window_size[0],window_size[1],"mini Golf");
    while(true){
        update(window,ball,mousePosition,playgrounds,click,release,is_clicked,game,NumOfShots);
        draw(window,ball,mousePosition,playgrounds,click,release,is_clicked,game, NumOfShots);
        delay(15);
    }
    return 0;
}