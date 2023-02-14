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

bool Date::less_than_15hours(Date departure){
    int minutes;
    minutes=24*60*(departure.get_date()-day)+60*(departure.get_hour()-hour)-minute+departure.get_minute();
    //cout << minutes<<endl;
    if(minutes <= 60*15 & minutes >0){
        return true;
    }
    return false;
}

void Date::show_duration(Date departure){
    int minutes;
    minutes=24*60*(departure.get_date()-day)+60*(departure.get_hour()-hour)-minute+departure.get_minute();
    int hour = minutes/60;
    minutes=minutes-hour*60;
    cout << hour <<"h "<< minutes <<"m";
}