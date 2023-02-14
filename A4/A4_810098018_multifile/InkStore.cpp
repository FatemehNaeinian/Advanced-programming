#include "InkStore.hpp"
#include <iostream>
using namespace std;
#define CHARGE_RED 1000
#define CHARGE_BLACK 1000
#define CHARGE_GREEN 1000
#define CHARGE_BLUE 1000
#define CHARGE_PAPER 100

InkStore::InkStore(int red_amount , int green_amount , int blue_amount , int black_amount){
    red=red_amount;
    blue=blue_amount;
    black=black_amount;
    green=green_amount;
}

void InkStore::charge_inkStore(){
    red=CHARGE_RED;
    blue=CHARGE_BLUE;
    black=CHARGE_BLACK;
    green=CHARGE_GREEN;
}

int InkStore::has_more_ink(InkStore orderInk , int ratio){
    if( ( red > ratio*orderInk.get_red() ) && ( black > ratio * orderInk.get_black() ) &&
        ( blue > ratio*orderInk.get_blue() ) && ( green > ratio*orderInk.get_green() ) ){
        return 0;
    }
    return 1;
}

int InkStore::get_red(){ return red; }
int InkStore::get_blue(){ return blue; }
int InkStore::get_black(){ return black; }
int InkStore::get_green(){ return green; }

void InkStore::show_info_InkStore(){
    cout<< "red: " << (int)red << endl;
    cout<< "green: " << (int)green << endl;
    cout<< "blue: " << (int)blue << endl;
    cout<< "black: " << (int)black << endl;
}

void InkStore::update_InkStore(InkStore inkOrder , int ratio){
    red = red-(ratio * inkOrder.get_red());
    blue = blue-(ratio * inkOrder.get_blue());
    green = green-(ratio * inkOrder.get_green());
    black = black-(ratio * inkOrder.get_black());
}
