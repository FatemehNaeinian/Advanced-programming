#ifndef FILTER_H
#define FILTER_H "FILTER_H"
#include "flight.hpp"
#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Filter{
public:
    Filter();
    void add_filter(string origin, string dest,vector<Flight>& flights);
    void add_filter(string airline , vector<Flight>& flights);
    void add_filter(string max_or_min , double max_or_min_price , vector<Flight>& flights);
    void add_filter(double min_price , double max_price , vector<Flight>& flights);
    void add_filter(int date,vector<Flight>& flights);
    void add_filter(int date,string min_departure_time,string max_departure_time,vector<Flight>& flights);
    void add_filter(int date,char max_or_min,string max_or_min_departure_time,vector<Flight>&flights);
    void apply_filter(vector<Flight>& flights);
    void free_filter();
    void show_flights();
private:
    vector<Flight*> filtered;
    bool first_time;
    bool airline_filter;
    bool time_filter;
    string type_time_filter;
    bool price_fliter;
    string type_price_filter;
    bool origin_dest_filter;
    string origin_city;
    string dest_city;
    double price_min;
    double price_max;
    string airline_company;
    int departure_date;
    string departure_min_time;
    string departure_max_time;
};

#endif
