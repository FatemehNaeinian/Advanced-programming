#include "Press.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;
#define Time_UNIT 1

int main(){
    Press press;
    int NumOfPrinters;
    int NumOfOrders;
    string command;

    while(cin >> command){
        if(command=="add_printer"){
            int speed;
            cin >> speed;
            press.add_printer(speed);
            cout << "printer added successfully" << endl;
        }

        else if(command=="add_order"){
            int red , green , blue , black , paper;
            string type;
            cin >> red >> green >> blue >> black >> paper >> type;
            press.add_order(red , green , blue , black , paper , type);
            cout << "order added successfully" << endl;
        }

        else if(command=="advance_time"){
            int timeUnit;
            cin >> timeUnit;
            press.do_process(timeUnit);
            cout << "ok" << endl;
        }

        else if(command=="show_press_info"){
            press.show_info_Press();
        }

        else if(command=="finish"){
            press.finish();
        }

        else{
            cerr << "unknown command\n";
			abort();
        }
    }
}