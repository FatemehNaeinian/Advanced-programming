#include "person.hpp"
#include "flight.hpp"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

Person::Person(string user , string pass){
    username = user;
    password = pass;
    money = 0.0;
}

string Person::get_username(){
    return username;
}

string Person::get_password(){
    return password;
}

void Person::increase_money(double amount){
    money += amount;
}

void Person::show_info(){
    cout << username <<" " << password << " " << money <<endl;
}

bool Person::has_enough_money(Flight* current ,int quantity ,string flight_class){
    if(money > current->total_costs(quantity ,flight_class)){
        return true;
    }
    return false;
}

void Person::buy_tickets(Flight* current ,int quantity ,string flight_class ,int tickets_count ,string type){
    tickets.push_back(Ticket(current, quantity ,flight_class ,tickets_count ,type));
    money -= tickets[tickets.size()-1].cost_of_ticket();
}

void Person::show_tickets(){
    if(tickets.size()==0){
        cout << "EMPTY" << endl;
        return;
    }
    int ticket_count=0;
    for(int i=0 ; i<tickets.size() ; i++){
        if(tickets[i].is_available()){
            tickets[i].show_info();
            ticket_count++;
        }
    }
    if(ticket_count ==0 ){
        cout << "EMPTY" << endl;
        return; 
    }
}

void Person::show_specific_ticket(int id){
    for(int i=0; i< tickets.size() ; i++){
        if(tickets[i].get_ID() == id){
            if(tickets[i].is_available()){
                tickets[i].show_info();
                return;
            }
            else{
                cout << "Not Found" <<endl;
                return;
            }
        }
    }
    cout << "Not Found" <<endl;
}


void Person::delete_ticket(int id){
    for(int i=0; i< tickets.size() ; i++){
        if(tickets[i].get_ID() == id){
            if(tickets[i].is_available()){
                if(tickets[i].get_type() == "refundable"){
                    tickets[i].delete_ticket();
                    money += 0.5* tickets[tickets.size()-1].cost_of_ticket();
                    cout << "OK" << endl;
                    return;
                }
                else{
                    cout << "Bad Request" << endl;
                    return;
                }
            }
            else{
                cout << "Not Found" <<endl;  
                return;
            }
        }
    }
    cout << "Not Found" <<endl;    
}