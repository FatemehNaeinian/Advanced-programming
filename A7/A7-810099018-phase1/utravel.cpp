#include "utravel.hpp"
#include "person.hpp"
#include "filter.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
const char fileDelimeter=',';
const char timeDelimeter=':';
const char Delimeter=' ';

Utravel::Utravel(){
    logedIn=false;
    tickets_count=0;
}

void Utravel::add_flight(string filename){
    ifstream inputFile;
    inputFile.open(filename);
    if(!inputFile.is_open()){
        cerr << "failed in opening file "<<filename<<endl;
        return ;
    }
    int flightNum=0;
    string line,temp;
    getline(inputFile,line);
    while(inputFile.good()){
        flightNum++;
        string airline , origin , dest , dep_time , arr_time ;
        int seats , arrival_day , departure_day ,dep_hour , dep_minute , arr_hour , arr_minute;
        double cost;
        getline(inputFile,line);
        stringstream lineStream(line);
        getline(lineStream,temp,fileDelimeter);
        airline = temp ;

        getline(lineStream,temp,fileDelimeter);
        origin = temp ;
        getline(lineStream,temp,fileDelimeter);
        dest = temp ;
        getline(lineStream,temp,fileDelimeter);
        departure_day = stoi(temp);
        getline(lineStream,temp,fileDelimeter);
        dep_time = temp ;
        seperate_time(dep_hour,dep_minute ,dep_time);
        getline(lineStream,temp,fileDelimeter);
        arrival_day = stoi(temp) ;
        getline(lineStream,temp,fileDelimeter);
        arr_time = temp ;
        seperate_time(arr_hour,arr_minute ,arr_time);
        getline(lineStream,temp,fileDelimeter);
        seats = stoi(temp);
        getline(lineStream,temp,fileDelimeter);
        istringstream(temp) >> cost;
        flights.push_back(Flight(flightNum,airline ,origin ,dest ,seats ,arrival_day ,departure_day ,dep_hour ,dep_minute ,arr_hour ,arr_minute , cost));
    }
}

void Utravel::seperate_time(int& hour,int& minute ,string timeInput){
    string temp;
    stringstream time(timeInput);
    getline(time,temp,timeDelimeter);
    hour=stoi(temp);
    getline(time,temp,timeDelimeter);
    minute=stoi(temp);
}

void Utravel::commands(){
    string command;
    while(cin >> command){
        if(command == "GET"){
            GET();
        }
        if(command == "POST"){
            POST();
        }
        if(command == "DELETE"){
            DELETE();
        }
    }
}

void Utravel::POST(){
    string post_type , questionMark;
    cin >> post_type;
    if(post_type == "signup"){
        cin >> questionMark;
        if(questionMark == "?"){
            SIGNUP();
        }
        else{
            cout << "Bad Request" << endl;
        }
    }
    if(post_type == "login"){
        cin >> questionMark;
        if(questionMark == "?"){
            LOGIN();
        }
        else{
            cout << "Bad Request" << endl;
        }        
    }
    if(post_type == "logout"){
        if(logedIn){
           LOGOUT(); 
        }
        else{
            cout << "Permission Denied" <<endl;
        }
    }
    if(post_type == "wallet"){
        if(logedIn){
            cin >> questionMark;
            if(questionMark == "?"){
                WALLET();
            } 
            else{
                cout << "Bad Request" << endl;
            } 
        }
        else{
            cout << "Permission Denied" <<endl;
        }  
    }
    if(post_type == "filters"){
        if(logedIn){
            cin >> questionMark;
            if(questionMark == "?"){
                FILTER();
            } 
            else{
                cout << "Bad Request" << endl;
            } 
        }
        else{
            cout << "Permission Denied" <<endl;
        }  
    }
    if(post_type == "tickets"){
        if(logedIn){
            cin >> questionMark;
            if(questionMark == "?"){
                TICKET();
            } 
            else{
                cout << "Bad Request" << endl;
            } 
        }
        else{
            cout << "Permission Denied" <<endl;
        }  
    }    
}

void Utravel::SIGNUP(){
    string input, username , password;
    cin >> input;
    for(int i=0;i<2;i++){
        if(input == "username"){
            cin >> username;
        }
        if(input == "password"){
            cin >> password;
        }
        if(i==0){
            cin >> input;
        }
    }
    if(check_user_is_new(username)){
        users.push_back(Person(username , password));
        cout << "OK" <<endl;
        logedIn=true;
        current_user=&users[users.size()-1];
    }
    else{
        cout << "Bad Request" <<endl;
    }
}

bool Utravel::check_user_is_new(string user){
    for(int i=0 ; i<users.size() ; i++){
        if(users[i].get_username()==user){
            return false;
        }
    }
    return true;
}

void Utravel::LOGIN(){
    string input , username , password ;
    cin >> input;
    for(int i=0;i<2;i++){
        if(input == "username"){
            cin >> username;
        }
        if(input == "password"){
            cin >> password;
        }
        if(i==0){
            cin >> input;
        }
    }
    int userNum=0;
    if(find_user_to_login(username , password ,userNum)){
        current_user=&users[userNum];
        logedIn=true;
        cout << "OK" <<endl;
    }
    else{
        cout << "Bad Request" <<endl;
    }
}

bool Utravel::find_user_to_login(string username ,string password ,int& userNum){
    for(int i=0;i<users.size() ; i++){
        if(users[i].get_username()==username){
            if(users[i].get_password()==password){
                userNum=i;
                return true;
            }
        }
    }
    return false;
}

void Utravel::LOGOUT(){
    logedIn=false;
    current_user = NULL;
    filter= NULL;
    cout << "OK" <<endl;
}

void Utravel::WALLET(){
    string input , amountstr;
    double amount;
    cin >> input;
    if(input == "amount"){
        cin >> amountstr;
        istringstream(amountstr) >> amount;
        if(amount > 0){
            current_user->increase_money(amount);
            cout << "OK" << endl;
        }
        else{
            cout << "Bad Request" <<endl;
        }
    }
}

void Utravel::GET(){
    if(logedIn==false){
        cout << "Permission Denied" << endl;
        return;
    }
    string line , input;
    string get_type , questionMark;
    getline(cin , line);
    stringstream lineStream(line);
    getline(lineStream,input,Delimeter);
    getline(lineStream,get_type,Delimeter);
    if(get_type == "flights"){
        getline(lineStream,input,Delimeter);
        if(input == "?"){
            show_specific_flight(lineStream);
        }
        else{
            show_flights();
            return;           
        }
    }
    if(get_type == "tickets"){
        getline(lineStream,input,Delimeter);
        if(input == "?"){
            show_specific_ticket(lineStream);
        }
        else{
            show_tickets();
            return;           
        }
    }
    else{
        cout << "Not found" << endl;
    } 
}

void Utravel::show_specific_ticket(stringstream& lineStream){
    string input ;
    int id;
    getline(lineStream,input,Delimeter);
    if(input == "id"){
        getline(lineStream,input,Delimeter);
        istringstream(input) >> id;
        if(id > 0 && id <= tickets_count){
            current_user->show_specific_ticket(id);
            return;
        }
        else{
            cout << "Not Found" <<endl;
        }
    }
}

void Utravel::show_tickets(){
    current_user->show_tickets();
}

void Utravel::show_specific_flight(stringstream& lineStream){
    string input ;
    int id;
    int count_flight=0;
    getline(lineStream,input,Delimeter);
    if(input == "id"){
        getline(lineStream,input,Delimeter);
        istringstream(input) >> id;
        if(id > 0 && id < flights.size()){
            flights[id-1].show_info(count_flight);
            return;
        }
        if(count_flight==0){
            cout << "Empty" << endl;
            return;
        }
        else{
            cout << "Not Found" <<endl;
        }
    }
}

void Utravel::show_flights(){
    if(filter == NULL){
        int count_flight=0;
        for(int i=0 ; i<flights.size() ; i++){
            flights[i].show_info(count_flight);
        }
        if(count_flight==0){
            cout << "Empty" << endl;
        }        
    }
    else{
        filter->show_flights();
    }
}

void Utravel::DELETE(){
    string input;
    cin >> input;
    if(logedIn==true){
        if(input == "filters"){
            filter= NULL;
            cout << "OK" << endl;
        }
        if(input == "tickets"){
            cin >> input;
            if(input == "?"){
                delete_ticket();
            }
        }        
    }
}

void Utravel::delete_ticket(){
    string input;
    cin >> input;
    if(input == "id"){
        int id;
        cin >> id;
        if(id<1 || id > tickets_count){
            cout << "Not Found" << endl;
        }
        else{
            current_user->delete_ticket(id);
        }
    }
}

void Utravel::FILTER(){
    if(filter == NULL){
        filter= new Filter();
    }
    string line , input;
    getline(cin , line);
    stringstream lineStream(line);
    getline(lineStream,input,Delimeter);
    getline(lineStream,input,Delimeter);
    if(input == "from" || input == "to"){
        string origin , dest;
        if(input == "from"){
            getline(lineStream,origin,Delimeter);
            getline(lineStream,input,Delimeter);
            if(input == "to"){
                getline(lineStream,dest,Delimeter);
                filter->add_filter(origin,dest,flights);
                return;
            }
        }
        if(input == "to"){
            getline(lineStream,dest,Delimeter);
            getline(lineStream,input,Delimeter);
            if(input == "from"){
                getline(lineStream,origin,Delimeter);
                filter->add_filter(origin,dest,flights);
                return;
            }
        }
    }
    if(input == "airline"){
        string airline;
        getline(lineStream,airline,Delimeter);
        filter->add_filter(airline,flights);
        return;
    }
    if(input == "min_price" || input == "max_price" ){
        double min_price , max_price;
        if(input == "min_price"){
            getline(lineStream,input,Delimeter);
            istringstream(input) >> min_price;
            if( min_price <0 ){
                cout << "Bad Request" << endl;
                return;
            }
            getline(lineStream,input,Delimeter);
            if(input == "max_price"){ 
                getline(lineStream,input,Delimeter);
                istringstream(input) >> max_price;
                if( max_price <0 || max_price < min_price){
                    cout << "Bad Request" << endl;
                    return;
                }
                filter->add_filter(min_price,max_price,flights);
                return;
            }
            else{
                filter->add_filter("min" ,min_price,flights);
                return;
            }
        }
        if(input == "max_price"){
            getline(lineStream,input,Delimeter);
            istringstream(input)  >> max_price;
            if( max_price <0 ){
                cout << "Bad Request" << endl;
                return;
            }
            getline(lineStream,input,Delimeter);
            if(input == "min_price"){
                getline(lineStream,input,Delimeter);
                istringstream(input)  >> min_price;
                if( min_price <0 || max_price < min_price){
                    cout << "Bad Request" << endl;
                    return;
                }
                filter->add_filter(min_price,max_price,flights);
                return;
            }
            else{
                filter->add_filter("max" ,max_price,flights);
                return;
            }
        }
        else{
            cout << "Bad Request" << endl;
            return;
        }
    }
    if(input == "departure_date" || input == "min_departure_time" || input == "max_departure_time"){
        int date=0 ;
        string min_departure_time;
        string max_departure_time ;
        while(true){
            if(input == "departure_date"){
                getline(lineStream,input,Delimeter);
                istringstream(input)  >> date;
            }
            if(input == "min_departure_time"){
                getline(lineStream,input,Delimeter);
                istringstream(input)  >> min_departure_time;
            }
            if(input == "max_departure_time"){
                getline(lineStream,input,Delimeter);
                istringstream(input)  >> max_departure_time;
            }
            getline(lineStream,input,Delimeter);
            if(input == ""){
                break;
            }
        }
        if(date <= 0){
            cout << "Bad Request" <<endl;
            return;
        }
        if(min_departure_time.empty() && max_departure_time.empty()){
            filter->add_filter(date,flights);
            return;
        }
        if(min_departure_time.empty()){
            filter->add_filter(date,'x',max_departure_time,flights);
            return;
        }
        if(max_departure_time.empty()){
            filter->add_filter(date,'n',min_departure_time,flights);
            return;
        }
        else{
            filter->add_filter(date,min_departure_time,max_departure_time,flights);
            return;
        }
    }
}

void Utravel::TICKET(){
    string line , input;
    getline(cin , line);
    stringstream lineStream(line);
    getline(lineStream,input,Delimeter);
    int i=0;
    int flight_id , quantity;
    string flight_class,type;
    while(i<4){
        getline(lineStream,input,Delimeter);
        if(input=="flight"){
            getline(lineStream,input,Delimeter);
            istringstream(input) >> flight_id;
        }
        if(input=="quantity"){
            getline(lineStream,input,Delimeter);
            istringstream(input) >> quantity;
        }
        if(input=="class"){
            getline(lineStream,flight_class,Delimeter);
        }
        if(input=="type"){
            getline(lineStream,type,Delimeter);
        }
        i++;
    }
    if(flight_id <1 || flight_id > flights.size()){
        cout << "Not Found" << endl;
        return;
    }
    Flight* current=find_flight(flight_id);
    if(!current->has_enough_quantity(flight_class,quantity)){
        cout << "Bad Request"<<endl;
        return;
    }
    if(!current_user->has_enough_money(current , quantity ,flight_class)){
        cout << "Bad Request"<<endl;
        return;
    }
    tickets_count++;
    current_user->buy_tickets(current , quantity ,flight_class , tickets_count , type);
    cout << tickets_count<<endl;
}

Flight* Utravel::find_flight(int flight_id){
    return &flights[flight_id-1];
}

