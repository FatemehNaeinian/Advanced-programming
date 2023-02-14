#include "date.hpp"
#include <iostream>
#include <vector>
#include <string>
using namespace std;


Date::Date(int day_ , int hour_ , int minute_){
    day = day_;
    hour = hour_;
    minute = minute_;
}


void Date::show_date(){
    cout << day << " ";
    if(hour>9){
        cout << hour << ":";
    }
    if(hour<10){
        cout << "0"<<hour << ":";
    }   
    if(minute>9){
        cout << minute << " ";
    }
    if(minute<10){
        cout << "0" << minute <<" ";
    }        
}

int Date::get_date(){return day;}
int Date::get_hour(){return hour;}
int Date::get_minute(){return minute;}