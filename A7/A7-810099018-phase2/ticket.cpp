#include "ticket.hpp"
#include "flight.hpp"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

Ticket::Ticket(Flight* flight ,int quantity_ ,string flight_class ,int tickets_count ,string type){
    ticket_ID = tickets_count;
    class_of_flight = flight_class;
    type_of_ticket = type;
    quantity = quantity_ ;
    active_or_deleted = true;
    flight_ticket = flight;
    flight_ticket->decrease_seats(class_of_flight , quantity);
}

void Ticket::show_info(){
    cout << ticket_ID << " ";
    flight_ticket->show_ID_airline();
    cout << " "<< quantity << " " ;
    flight_ticket->show_info_for_ticket();
    cout << class_of_flight << " " << type_of_ticket << " ";
    flight_ticket->show_costs(quantity , class_of_flight);
}

bool Ticket::is_available(){
    return active_or_deleted ;
}

int Ticket::get_ID(){
    return ticket_ID;
}

void Ticket::delete_ticket(){
    active_or_deleted = false;
    flight_ticket->increase_seats(class_of_flight , quantity);
}

double Ticket::cost_of_ticket(){
    return (double)quantity * flight_ticket->total_costs(quantity ,class_of_flight);
}

string Ticket::get_type(){
    return type_of_ticket;
}