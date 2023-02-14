#include "flight.hpp"
#include "date.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>
using namespace std;
const char timeDelimeter=':';


Flight::Flight(int Num,string airline_ ,string origin_ ,string dest ,int seats_ ,int arrival_day ,int departure_day ,int dep_hour ,int dep_minute ,int arr_hour ,int arr_minute , double cost_)
    :departure(departure_day , dep_hour , dep_minute ) ,arrival(arrival_day, arr_hour ,arr_minute )
{
    flightNum = Num;
    airline = airline_;
    origin = origin_;
    destination = dest;
    seats = seats_;
    cost = cost_;
    buisnessSeats = ceil(0.25 * seats);
    economySeats = seats - buisnessSeats;
    economyCost = cost;
    buisnessCost = 2.5 * cost;
}

void Flight::show_info(int& count_flight){
    if((economySeats + buisnessSeats )>0){
        count_flight++;
        cout<< flightNum << " "<< airline << " "<< origin << " "<< destination<< " ";
        departure.show_date();
        arrival.show_date();
        cout<< economySeats + buisnessSeats << " "<<fixed << setprecision(2) << cost <<endl;  
    }
}

bool Flight::is_origin_and_dest_the_same(string origin_ ,string dest_){
    if(origin == origin_ && destination == dest_){
        return true;
    }
    return false;
}

bool Flight::is_airline_the_same(string airlinee){
    if(airline == airlinee){
        return true;
    }
    return false;
}
bool Flight::is_price_in_range(string max_or_min ,double max_or_min_price){
    if(max_or_min == "max"){
        if(cost <= max_or_min_price ){
            return true;
        }
        return false;
    }
    if(max_or_min == "min"){
        if(cost >= max_or_min_price ){
            return true;
        }
    }
    return false;
}
bool Flight::is_price_in_range(double min_price ,double max_price){
    if(cost <= max_price && cost >= min_price){
        return true;
    }
    return false;
}

bool Flight::is_in_this_time(int date_){
    if(date_ == departure.get_date()){
        return true;
    }
    return false;
}

bool Flight::is_in_this_time(int date_ ,string min_departure_time ,string max_departure_time){
    int min_hour , min_minute , max_hour , max_minute;
    seperate_time(min_hour,min_minute,min_departure_time);
    seperate_time(max_hour,max_minute,max_departure_time);
    int remain_time_to_max=60*(max_hour-departure.get_hour())+ max_minute-departure.get_minute();
    int time_after_min=60*(departure.get_hour()-min_hour)- min_minute+departure.get_minute();
    if(date_ == departure.get_date() && remain_time_to_max >=0 && time_after_min >=0){
        return true;
    }
    return false;
}

bool Flight::is_in_this_time(int date_ ,char max_or_min ,string max_or_min_departure_time){
    if(max_or_min=='n'){
        int min_hour , min_minute;
        seperate_time(min_hour,min_minute,max_or_min_departure_time);
        int time_after_min=60*(departure.get_hour()-min_hour)- min_minute+departure.get_minute();
        if(date_ == departure.get_date()&& time_after_min >=0){
            return true;
        }
        return false;
    }
    if(max_or_min=='x'){
        int max_hour , max_minute;
        seperate_time(max_hour,max_minute,max_or_min_departure_time);
        int remain_time_to_max=60*(max_hour-departure.get_hour())+ max_minute-departure.get_minute();
        if(date_ == departure.get_date() && remain_time_to_max >=0 ){
            return true;
        }
    }
    return false;
}

void Flight::seperate_time(int& hour,int& minute ,string timeInput){
    string temp;
    stringstream time(timeInput);
    getline(time,temp,timeDelimeter);
    hour=stoi(temp);
    getline(time,temp,timeDelimeter);
    minute=stoi(temp);
}

bool Flight::has_enough_quantity(string flight_class,int quantity){
    if(flight_class=="economy"){
        if(economySeats >= quantity){
            return true;
        }
    }
    if(flight_class=="business"){
        if(buisnessSeats >= quantity){
            return true;
        }
    }
    return false;
}

double Flight::total_costs(int quantity ,string flight_class){
    if(flight_class=="economy"){
        return (double)quantity * economyCost; 
    }
    else{
        return (double)quantity * buisnessCost; 
    }
}

void Flight::show_ID_airline(){
    cout << flightNum << " " << airline ;
}

void Flight::show_info_for_ticket(){
    cout<< origin << " "<< destination<< " ";
    departure.show_date();
    arrival.show_date(); 
}

void Flight::show_costs(int quantity ,string class_of_flight){
    if(class_of_flight == "economy"){
        cout  << fixed << setprecision(2) << (double)quantity *economyCost <<endl;
    }
    else{
        cout  << fixed << setprecision(2) << (double)quantity *buisnessCost <<endl;
    }
}


void Flight::increase_seats(string class_of_flight ,int quantity){
    if(class_of_flight == "economy"){
        economySeats += quantity;
    }
    else{
        buisnessSeats += quantity;
    }
}


void Flight::decrease_seats(string class_of_flight ,int quantity){
    if(class_of_flight == "economy"){
        economySeats -= quantity;
    }
    else{
        buisnessSeats -= quantity;
    }
}