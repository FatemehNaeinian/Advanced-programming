#ifndef PRESS_H
#define PRESS_H "PRESS_H"
#include "Printer.hpp"
#include "Order.hpp"
#include "InkStore.hpp"
#include <string>
#include <vector>
class Press {
public:
    Press(int startTime = 0);
    void add_printer(int print_speed);
    void add_order(int red , int green , int blue , int black , int paper , string type);
    void start_printing(int j); 
    void do_process(int timeUnit);
    void show_info_Press();
    void finish();
    Order* Nobat_kie();
    int is_there_any_order();

private:
    vector<Printer> printers;
    vector<Order> orders;
    int time;
};

#endif