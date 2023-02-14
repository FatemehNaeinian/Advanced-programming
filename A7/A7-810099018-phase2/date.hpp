#ifndef DATE_H
#define DATE_H "DATE_H"
#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Date{
public:
    Date(int day_ , int hour_ , int minute_);
    void show_date();
    int get_date();
    int get_hour();
    int get_minute();
    bool less_than_15hours(Date arrival);
    void show_duration(Date arrival);
private:
    int day;
    int hour;
    int minute;

};
#endif