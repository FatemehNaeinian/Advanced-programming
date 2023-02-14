#include "Printer.hpp"
#include "InkStore.hpp"
#include "Order.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define CHARGE_PAPER 100

#define Time_UNIT 1

Printer::Printer(int print_speed , int ID_number){
    ID = ID_number;
    speed = print_speed;
    paperStore = CHARGE_PAPER;
    status = "idle";
    InkStore new_ink;
    ink = new_ink;
    issue = " ";
}

string Printer::get_status_printer(){ return status; }

void Printer::get_order(Order* order){
    currentOrder = order;
}

int Printer::check_store(){
    InkStore orderInk = currentOrder->get_ink();
    if((paperStore < speed) && (paperStore<currentOrder->get_remainPaper_Order())){
        return -1;
    }
    if(ink.has_more_ink(orderInk ,speed) && ink.has_more_ink(orderInk ,currentOrder->get_remainPaper_Order())){
        return -2;
    }
    return 0;
}

void Printer::update_printer(){
    paperStore = paperStore-speed;
    ink.update_InkStore(currentOrder->get_ink(),speed);
}

void Printer::end_of_printing_printer(){
    paperStore = paperStore-currentOrder->get_remainPaper_Order();
    ink.update_InkStore(currentOrder->get_ink(),currentOrder->get_remainPaper_Order());
}

void Printer::do_process_when_there_is_enough_paper_and_ink(){
    status="busy";
    int neededTime = currentOrder->needed_timeUnit(speed);
    if(neededTime>Time_UNIT){
        currentOrder->update_Orders(speed);
        update_printer();
        return;
    }
    else{
        end_of_printing_printer();
        currentOrder->end_of_printing_Orders(speed);
        return;
    }
}

void Printer::make_printer_unavailable(int check){
    status="not_available";
    if(check==-1){
        remainTimeUnit=5;
        currentOrder->increase_time(5);
        issue = "paper";
    }
    else if(check==-2){
        remainTimeUnit=10;
        currentOrder->increase_time(10);
        issue = "ink";
    }  
    return;
}

void Printer::do_process_Printer(){
    if(currentOrder->get_remainPaper_Order()==0){
        status = "idle";
        return;
    }

    int check = check_store();
    if(check==0){
        do_process_when_there_is_enough_paper_and_ink();
        return;
    }
    else{
        make_printer_unavailable(check);
        return;          
    }
}

void Printer::fill_stores(){
    if(remainTimeUnit==1){
        remainTimeUnit = 0;
        if(issue == "paper"){
            paperStore = CHARGE_PAPER;
        }
        if(issue == "ink"){
            ink.charge_inkStore();
        }
        status = "busy";
        return;
    }
    else{
        remainTimeUnit--;
        return;
    }
}

void Printer::show_info_Printer(){
    cout << "printer ID: " << ID << endl;
    cout << "status: " << status << endl;
    if(status=="busy" | status=="not_available"){
        cout << "current order: " << currentOrder->get_ID_Order() << " " << currentOrder->get_remainPaper_Order() << endl;
    }
    cout << "ink left:" << endl;
    ink.show_info_InkStore();
    cout << "papers left: " << paperStore << endl;
    return;
}
