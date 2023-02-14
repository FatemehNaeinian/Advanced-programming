#include "Press.hpp"
#include "Printer.hpp"
#include "InkStore.hpp"
#include "Order.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define Time_UNIT 1

Press::Press(int startTime){
    time = 0;
}

void Press::add_printer(int print_speed){
    printers.push_back(Printer(print_speed , printers.size()+1));

}

void Press::add_order(int red , int green , int blue , int black , int paper , string type){
    orders.push_back(Order(red , green , blue , black , paper , type,orders.size()+1));
}

void Press::start_printing(int j){
    if(orders.size()>is_there_any_order()){
        Order* orderiKeNobateshe=Nobat_kie();
        printers[j].get_order(orderiKeNobateshe);
        printers[j].do_process_Printer();
    }
}

void Press::do_process(int timeUnit){
    time = time+timeUnit;
    for(int i=0 ; i<timeUnit ; i++){
        for(int j=0 ; j<printers.size() ; j++){
            if(printers[j].get_status_printer()=="not_available"){
                printers[j].fill_stores();
            } 
            if(printers[j].get_status_printer()=="busy"){
                printers[j].do_process_Printer();
            }
            if(printers[j].get_status_printer()=="idle"){
                start_printing(j);
            }  
        }
    }
}

void Press::show_info_Press(){
    cout << "elapsed time: " << time << endl;
    cout << "VIP orders queue:" << endl;
    for(int i=0 ; i<orders.size() ; i++){
        if(orders[i].get_typeOfOrder()=="vip"&&orders[i].get_state_order()=="inLine"){
            orders[i].show_info_Orders();
        }
    }
    cout << "\nregular orders queue:" << endl;
    for(int i=0 ; i<orders.size() ; i++){
        if(orders[i].get_typeOfOrder()=="regular"&&orders[i].get_state_order()=="inLine"){
            orders[i].show_info_Orders();
        }
    }
    cout << "\nprinters:" << endl;
    for(int i=0 ; i<printers.size() ; i++){
        printers[i].show_info_Printer();
        cout<<endl;
    }
    cout << "orders finished:" << endl;
    for(int i=0 ; i<orders.size() ; i++){
        if(orders[i].get_state_order()=="finished"){
            orders[i].show_finished_Orders();
        }
    }
    cout << endl;
}

void Press::finish(){
    while(true){
        int finishedOrders = 0;
        for(int i=0 ; i<orders.size() ; i++){
            if(orders[i].get_state_order()=="finished"){
                finishedOrders++;
            }
        }
        if(finishedOrders==orders.size()){
            cout<<time<<endl;
            break;
        }
        else{
            do_process(Time_UNIT);
        }
    }
}

Order* Press::Nobat_kie(){
    for(int i=0 ; i<orders.size() ; i++){
        if(orders[i].get_typeOfOrder()=="vip" && orders[i].get_state_order()=="inLine"){
            return &orders[i];
        }
    }
    for(int i=0 ; i<orders.size() ; i++){
        if(orders[i].get_typeOfOrder()=="regular" && orders[i].get_state_order()=="inLine"){
            return &orders[i];
        }
    }
}

int Press::is_there_any_order(){
    int finishedAndInProcessOrders=0;
    for(int i=0 ; i<orders.size() ; i++){
        if(orders[i].get_state_order()=="inProcess" || orders[i].get_state_order()=="finished"){
            finishedAndInProcessOrders++;
        }
    }
    return finishedAndInProcessOrders;
}
