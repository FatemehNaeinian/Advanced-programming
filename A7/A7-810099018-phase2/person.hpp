#ifndef PERSON_H
#define PERSON_H "PERSON_H"
#include "ticket.hpp"
#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Person{
public:
    Person(string user , string pass);
    string get_username();
    string get_password();
    void increase_money(double amount);
    void show_info();
    bool has_enough_money(Flight* current ,int quantity ,string flight_class);
    void buy_tickets(Flight* current ,int quantity ,string flight_class ,int tickets_count ,string type);
    void show_tickets();
    void show_specific_ticket(int id);
    void delete_ticket(int id);
private:
    string username;
    string password;
    double money;
    vector<Ticket> tickets;

};

#endif