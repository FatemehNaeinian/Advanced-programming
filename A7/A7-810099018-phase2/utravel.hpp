#ifndef UTRAVEL_H
#define UTRAVEL_H "UTRAVEL_H"
#include "flight.hpp"
#include "person.hpp"
#include "filter.hpp"
#include "compare.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class Utravel{
public:
    Utravel();
    void add_flight(string filename);
    void seperate_time(int& hour,int& minute ,string timeInput);
    void commands();
    void POST();
    void GET();
    void DELETE();
    void SIGNUP();
    bool check_user_is_new(string user );
    void LOGIN();
    bool find_user_to_login(string username ,string password ,int& userNum);
    void LOGOUT();
    void WALLET();
    void FILTER();
    void TICKET();
    void show_specific_flight(stringstream& lineStream);
    void show_flights();
    void show_specific_ticket(stringstream& lineStream);
    void show_tickets();
    void delete_ticket();
    Flight* find_flight(int flight_id);
    void connecting_flights(stringstream& lineStream);
    vector<Flight*> find_connecting_flights(string origin ,string dest);
    void cheapest_flight(stringstream& lineStream);
    void find_and_show_cheapest(vector<Flight*> connecting , vector<Flight*> direct ,int connecting_count , int direct_count);
    vector<Flight*> find_direct_flights(string origin ,string dest ,int departure_date);
    vector<Flight*> find_connecting_flights(string origin ,string dest ,int departure_date);
    void overall_report();
    double average_flight_cost();
    double min_flight_cost();
    double max_flight_cost();
    string most_popular_dest();
    vector<string> top3_airline();
private:
    vector<Flight> flights;
    vector<Person> users;
    Person* current_user;
    bool logedIn;
    Filter* filter;
    int tickets_count;
};

#endif