#include "Order.hpp"
#include "InkStore.hpp"
#include <iostream>
#include <string>
#include <vector>
#define Time_UNIT 1

using namespace std;

Order::Order(int red , int green , int blue , int black , int numOfPaper , string type , int ID_number){
    ID = ID_number;
    paper = numOfPaper;
    typeOfOrder = type;
    state = "inLine";
    timeTaken=0;
    remainPaper=numOfPaper;
    InkStore new_ink(red ,green ,blue ,black);
    ink = new_ink;
}

InkStore Order::get_ink(){ return ink; } 
string Order::get_typeOfOrder(){ return typeOfOrder; }
string Order::get_state_order(){ return state; }
int Order::get_remainPaper_Order(){ return remainPaper; }
int Order::get_all_paper_Order(){ return paper; }
int Order::get_ID_Order(){ return ID; }

int Order::needed_timeUnit(int speed){
    int ratio = remainPaper/speed;
    if(remainPaper-(ratio*speed)>0){
        return ratio +1;
    }
    else{
        return ratio;
    }
}

void Order::update_Orders(int speed){
    remainPaper = remainPaper-speed*Time_UNIT;
    state = "inProcess";
    timeTaken++;
}

void Order::end_of_printing_Orders(int speed){
    remainPaper = 0;
    state = "finished";
    timeTaken++;
}

void Order::show_info_Orders(){
    cout << ID << " " << paper << endl;
}

void Order::show_finished_Orders(){
    cout << ID << " " << timeTaken << endl;
}

void Order::increase_time(int j){
    timeTaken = timeTaken+j;
}

