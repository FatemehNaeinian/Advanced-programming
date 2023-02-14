#ifndef PRINTER_H
#define PRINTER_H "PRINTER_H"
#include "InkStore.hpp"
#include "Order.hpp"
#include <string>
#include <vector>
using namespace std;

class Order;

class Printer {
public:
    Printer(int print_speed , int ID_number);
    string get_status_printer();
    void get_order(Order* order);
    int check_store();
    void update_printer();
    void end_of_printing_printer();
    void do_process_when_there_is_enough_paper_and_ink();
    void make_printer_unavailable(int check);
    void do_process_Printer();
    void fill_stores();
    void show_info_Printer();

private:
    int ID;
    int speed;
    int paperStore;
    InkStore ink;
    string status;
    Order* currentOrder;
    int remainTimeUnit;
    string issue;
};

#endif