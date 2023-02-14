#ifndef ticket_H
#define ticket_H "ticket_H"
#include "flight.hpp"
#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Ticket {
public:
    Ticket(Flight* flight ,int quantity_ ,string flight_class ,int tickets_count ,string type);
    void show_info();
    bool is_available();
    int get_ID();
    void delete_ticket();
    double cost_of_ticket();
    string get_type();
private:
    int ticket_ID;
    string class_of_flight;
    string type_of_ticket;
    int quantity;
    bool active_or_deleted;
    Flight* flight_ticket;
};

#endif