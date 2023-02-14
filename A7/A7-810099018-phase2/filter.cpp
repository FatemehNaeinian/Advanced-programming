#include "filter.hpp"
#include "flight.hpp"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

Filter::Filter(){
    first_time = true;
    airline_filter = false;
    time_filter = false;
    price_fliter = false;
    origin_dest_filter = false;
}

void Filter::show_flights(){
    int count_flight=0;
    for(int i=0 ; i<filtered.size() ;i++){
        filtered[i]->show_info(count_flight);
    }
    if(count_flight==0){
        cout << "Empty" << endl;
    } 
}

void Filter::apply_filter(vector<Flight>& flights){
    if(filtered.size() > 0){
        free_filter();
    }
    bool is_okay=true;
    int flight_count=0;
    for(int i=0 ; i<flights.size() ;i++){
        bool is_okay=true;
        if(airline_filter){
            is_okay *= flights[i].is_airline_the_same(airline_company);
        }
        if(origin_dest_filter){
            is_okay *= flights[i].is_origin_and_dest_the_same(origin_city ,dest_city);
        }
        if(time_filter){
            if(type_time_filter == "date"){
                is_okay *= flights[i].is_in_this_time(departure_date);
            }
            if(type_time_filter == "all"){
                is_okay *= flights[i].is_in_this_time(departure_date , departure_min_time , departure_max_time);
            }
            if(type_time_filter == "max"){
                is_okay *= flights[i].is_in_this_time(departure_date , 'x' , departure_max_time);
            }
            if(type_time_filter == "min"){
                is_okay *= flights[i].is_in_this_time(departure_date , 'n' , departure_min_time);
            }
        }
        if(price_fliter){
            if(type_price_filter == "all"){
                is_okay *= flights[i].is_price_in_range(price_min , price_max);
            }
            if(type_price_filter == "max"){
                is_okay *= flights[i].is_price_in_range("max" , price_max);
            }
            if(type_price_filter == "min"){
                is_okay *= flights[i].is_price_in_range("min" , price_min);
            }
        }
        if(is_okay==true){
            filtered.push_back(&flights[i]);
            flight_count++;  
        }
    }
    if(flight_count==0){
        cout << "Bad Request" <<endl;
    }
    if(flight_count>0){
        cout << "OK" <<endl;
    } 
}


void Filter::add_filter(string origin, string dest,vector<Flight>& flights){
    origin_dest_filter = true;
    origin_city = origin;
    dest_city = dest;    
    apply_filter(flights);
}

void Filter::add_filter(string airline , vector<Flight>& flights){
    airline_company = airline;
    airline_filter = true;
    apply_filter(flights);
}

void Filter::add_filter(string max_or_min , double max_or_min_price , vector<Flight>& flights){
    price_fliter = true;
    if(max_or_min == "max"){
        type_price_filter = "max";
        price_max = max_or_min_price;
    }
    if(max_or_min == "min"){
        type_price_filter = "min";
        price_min = max_or_min_price;
    }
    apply_filter(flights);
}

void Filter::add_filter(double min_price , double max_price , vector<Flight>& flights){
    type_price_filter = "all";
    price_fliter = true;
    price_max = max_price;
    price_min = min_price;
    apply_filter(flights);
}

void Filter::add_filter(int date,vector<Flight>& flights){
    type_time_filter = "date";
    departure_date = date;
    time_filter = true;
    apply_filter(flights);
}

void Filter::add_filter(int date,string min_departure_time,string max_departure_time,vector<Flight>& flights){
    type_time_filter = "all";
    departure_date = date;
    departure_max_time = max_departure_time;
    departure_min_time = min_departure_time;
    time_filter = true;
    apply_filter(flights);
}

void Filter::add_filter(int date,char max_or_min,string max_or_min_departure_time,vector<Flight>&flights){
    departure_date = date;
    time_filter = true;
    if(max_or_min == 'x'){
        type_time_filter = "max";
        departure_max_time = max_or_min_departure_time;
    }
    if(max_or_min == 'n'){
        type_time_filter = "min";
        departure_min_time = max_or_min_departure_time;
    }
    apply_filter(flights);
}

void Filter::free_filter(){
    int size=filtered.size();
    for(int i=0 ; i<size ; i++){
        filtered.pop_back();
    }
}