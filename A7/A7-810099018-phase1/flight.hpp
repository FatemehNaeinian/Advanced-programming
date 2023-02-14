#ifndef FLIGHT_H
#define FLIGHT_H "FLIGHT_H"
#include "date.hpp"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Flight{
public:
    Flight(int Num,string airline_ ,string origin_ ,string dest ,int seats ,int arrival_day ,int departure_day ,int dep_hour ,int dep_minute ,int arr_hour ,int arr_minute , double cost_);
    void show_info(int& count_flight);
    void seperate_time(int& hour,int& minute ,string timeInput);
    bool is_origin_and_dest_the_same(string origin_ ,string dest_);
    bool is_airline_the_same(string airlinee);
    bool is_price_in_range(string max_or_min ,double max_or_min_price);
    bool is_price_in_range(double min_price ,double max_price);
    bool is_in_this_time(int date_);
    bool is_in_this_time(int date_ ,string min_departure_time ,string max_departure_time);
    bool is_in_this_time(int date_ ,char max_or_min ,string max_or_min_departure_time);
    bool has_enough_quantity(string flight_class,int quantity);
    double total_costs(int quantity ,string flight_class);
    void show_ID_airline();
    void show_info_for_ticket();
    void show_costs(int quantity ,string class_of_flight);
    void increase_seats(string class_of_flight ,int quantity);
    void decrease_seats(string class_of_flight ,int quantity);

private:
    int flightNum;
    string airline;
    string origin;
    string destination;
    Date departure;
    Date arrival;
    int seats;
    double cost;
    int economySeats;
    int buisnessSeats;
    double economyCost;
    double buisnessCost;
};

#endif