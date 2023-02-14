#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

#define CHARGE_RED 1000
#define CHARGE_BLACK 1000
#define CHARGE_GREEN 1000
#define CHARGE_BLUE 1000
#define CHARGE_PAPER 100
#define Time_UNIT 1

class InkStore {
public:
    InkStore(int red_amount=CHARGE_RED , int green_amount=CHARGE_GREEN , int blue_amount=CHARGE_BLUE , int black_amount=CHARGE_BLACK){
        red=red_amount;
        blue=blue_amount;
        black=black_amount;
        green=green_amount;
    }

    void charge_inkStore(){
        red=CHARGE_RED;
        blue=CHARGE_BLUE;
        black=CHARGE_BLACK;
        green=CHARGE_GREEN;
    }

    int has_more_ink(InkStore orderInk , int ratio){
        if( ( red > ratio*orderInk.get_red() ) && ( black > ratio * orderInk.get_black() ) &&
            ( blue > ratio*orderInk.get_blue() ) && ( green > ratio*orderInk.get_green() ) ){
            return 0;
        }
        return 1;
    }

    int get_red(){ return red; }
    int get_blue(){ return blue; }
    int get_black(){ return black; }
    int get_green(){ return green; }

    void show_info(){
        cout<< "red: " << (int)red << endl;
        cout<< "green: " << (int)green << endl;
        cout<< "blue: " << (int)blue << endl;
        cout<< "black: " << (int)black << endl;
    }

    void update(InkStore inkOrder , int ratio){
        red = red-(ratio * inkOrder.get_red());
        blue = blue-(ratio * inkOrder.get_blue());
        green = green-(ratio * inkOrder.get_green());
        black = black-(ratio * inkOrder.get_black());
    }

private:
    int red;
    int green;
    int blue;
    int black;
};


class Order {
public:
    void add_order(int red , int green , int blue , int black , int numOfPaper , string type , int ID_number){
        ID = ID_number;
        paper = numOfPaper;
        typeOfOrder = type;
        state = "inLine";
        timeTaken=0;
        remainPaper=numOfPaper;
        InkStore new_ink(red ,green ,blue ,black);
        ink = new_ink;
    }

    InkStore get_ink(){ return ink; } 
    string get_typeOfOrder(){ return typeOfOrder; }
    string get_state(){ return state; }
    int get_remain_paper(){ return remainPaper; }
    int get_Num_of_paper(){ return paper; }
    int get_ID(){ return ID; }

    int needed_timeUnit(int speed){
        int ratio = remainPaper/speed;
        if(remainPaper-(ratio*speed)>0){
            return ratio +1;
        }
        else{
            return ratio;
        }
    }

    void update(int speed){
        remainPaper = remainPaper-speed*Time_UNIT;
        state = "inProcess";
        timeTaken++;
    }

    void end_of_printing(int speed){
        remainPaper = 0;
        state = "finished";
        timeTaken++;
    }

    void show_info(){
        cout << ID << " " << paper << endl;
    }

    void show_finished(){
        cout << ID << " " << timeTaken << endl;
    }

    void increase_time(int j){
        timeTaken = timeTaken+j;
    }

private:
    int ID;
    int paper;
    string typeOfOrder;
    string state;
    InkStore ink; 
    int remainPaper;
    int timeTaken;
};


class Printer {
public:
    void add_printer(int print_speed , int ID_number){
        ID = ID_number;
        speed = print_speed;
        paperStore = CHARGE_PAPER;
        status = "idle";
        InkStore new_ink;
        ink = new_ink;
        issue = " ";
    }

    string get_status(){ return status; }

    void get_order(Order* order){
        currentOrder = order;
    }

    int check_store(){
        InkStore orderInk = currentOrder->get_ink();
        if((paperStore < speed) && (paperStore<currentOrder->get_remain_paper())){
            return -1;
        }
        if(ink.has_more_ink(orderInk ,speed) && ink.has_more_ink(orderInk ,currentOrder->get_remain_paper())){
            return -2;
        }
        return 0;
    }

    void update_printer(){
        paperStore = paperStore-speed;
        ink.update(currentOrder->get_ink(),speed);
    }

    void end_of_printing_printer(){
        paperStore = paperStore-currentOrder->get_remain_paper();
        ink.update(currentOrder->get_ink(),currentOrder->get_remain_paper());
    }

    void do_process_when_there_is_enough_paper_and_ink(){
        status="busy";
        int neededTime = currentOrder->needed_timeUnit(speed);
        if(neededTime>Time_UNIT){
            currentOrder->update(speed);
            update_printer();
            return;
        }
        else{
            end_of_printing_printer();
            currentOrder->end_of_printing(speed);
            return;
        }
    }

    void make_printer_unavailable(int check){
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

    void do_process(){
        if(currentOrder->get_remain_paper()==0){
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

    void fill_stores(){
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

    void show_info(){
        cout << "printer ID: " << ID << endl;
        cout << "status: " << status << endl;
        if(status=="busy" | status=="not_available"){
            cout << "current order: " << currentOrder->get_ID() << " " << currentOrder->get_remain_paper() << endl;
        }
        cout << "ink left:" << endl;
        ink.show_info();
        cout << "papers left: " << paperStore << endl;
        return;
    }

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



class Press {
public:
    Press(int startTime = 0){
        time = 0;
    }

    void add_printer(int print_speed){
        printers.push_back(Printer());
        Printer* new_printer = &printers[printers.size()-1];
        new_printer->add_printer(print_speed , printers.size());
    }

    void add_order(int red , int green , int blue , int black , int paper , string type){
        orders.push_back(Order());
        Order* new_order = &orders[orders.size()-1];
        new_order->add_order(red , green , blue , black , paper , type,orders.size());
    }

    void start_printing(int j){
        if(orders.size()>is_there_any_order()){
            Order* orderiKeNobateshe=Nobat_kie();
            printers[j].get_order(orderiKeNobateshe);
            printers[j].do_process();
        }
    }
    
    void do_process(int timeUnit){
        time = time+timeUnit;
        for(int i=0 ; i<timeUnit ; i++){
            for(int j=0 ; j<printers.size() ; j++){
                if(printers[j].get_status()=="not_available"){
                    printers[j].fill_stores();
                } 
                if(printers[j].get_status()=="busy"){
                    printers[j].do_process();
                }
                if(printers[j].get_status()=="idle"){
                    start_printing(j);
                }  
            }
        }
    }

    void show_info(){
        cout << "elapsed time: " << time << endl;
        cout << "VIP orders queue:" << endl;
        for(int i=0 ; i<orders.size() ; i++){
            if(orders[i].get_typeOfOrder()=="vip"&&orders[i].get_state()=="inLine"){
                orders[i].show_info();
            }
        }
        cout << "\nregular orders queue:" << endl;
        for(int i=0 ; i<orders.size() ; i++){
            if(orders[i].get_typeOfOrder()=="regular"&&orders[i].get_state()=="inLine"){
                orders[i].show_info();
            }
        }
        cout << "\nprinters:" << endl;
        for(int i=0 ; i<printers.size() ; i++){
            printers[i].show_info();
            cout<<endl;
        }
        cout << "orders finished:" << endl;
        for(int i=0 ; i<orders.size() ; i++){
            if(orders[i].get_state()=="finished"){
                orders[i].show_finished();
            }
        }
        cout << endl;
    }

    void finish(){
        while(true){
            int finishedOrders = 0;
            for(int i=0 ; i<orders.size() ; i++){
                if(orders[i].get_state()=="finished"){
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

    Order* Nobat_kie(){
        for(int i=0 ; i<orders.size() ; i++){
            if(orders[i].get_typeOfOrder()=="vip" && orders[i].get_state()=="inLine"){
                return &orders[i];
            }
        }
        for(int i=0 ; i<orders.size() ; i++){
            if(orders[i].get_typeOfOrder()=="regular" && orders[i].get_state()=="inLine"){
                return &orders[i];
            }
        }
    }

    int is_there_any_order(){
        int finishedAndInProcessOrders=0;
        for(int i=0 ; i<orders.size() ; i++){
            if(orders[i].get_state()=="inProcess" || orders[i].get_state()=="finished"){
                finishedAndInProcessOrders++;
            }
        }
        return finishedAndInProcessOrders;
    }

private:
    vector<Printer> printers;
    vector<Order> orders;
    int time;
};



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
            press.show_info();
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
