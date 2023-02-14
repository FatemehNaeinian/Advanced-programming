#ifndef ORDER_H
#define ORDER_H "ORDER_H"
#include <string>
#include <vector>
#include "InkStore.hpp"

using namespace std;


class Order {
public:
    Order(int red , int green , int blue , int black , int numOfPaper , string type , int ID_number);
    InkStore get_ink();
    string get_typeOfOrder();
    string get_state_order();
    int get_remainPaper_Order();
    int get_all_paper_Order();
    int get_ID_Order();
    int needed_timeUnit(int speed);
    void update_Orders(int speed);
    void end_of_printing_Orders(int speed);
    void show_info_Orders();
    void show_finished_Orders();
    void increase_time(int j);

private:
    int ID;
    int paper;
    string typeOfOrder;
    string state;
    InkStore ink; 
    int remainPaper;
    int timeTaken;
};

#endif