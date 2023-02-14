#include "utravel.hpp"
#include "person.hpp"
#include "filter.hpp"
#include "compare.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
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
    if(get_type == "connecting_flights"){
        getline(lineStream,input,Delimeter);
        if(input == "?"){
            connecting_flights(lineStream);
        }
        else{
            cout << "Bad Request" << endl;
            return;           
        }  
    }
    if(get_type == "cheapest_flight"){
        getline(lineStream,input,Delimeter);
        if(input == "?"){
            cheapest_flight(lineStream);
        }
        else{
            cout << "Bad Request" << endl;
            return;           
        }  
    }
    if(get_type == "overall_report"){
        overall_report();
        return;
    }
    if(get_type != "overall_report" && get_type != "cheapest_flight" && get_type != "flights" && get_type != "tickets" && get_type != "connecting_flights"){
        cout << "Not found" << endl;
    } 
    
}

void Utravel::overall_report(){
    double average_cost = average_flight_cost();
    double min_cost = min_flight_cost();
    double max_cost = max_flight_cost();
    string most_popular_destination = most_popular_dest();
    vector<string> top_airline = top3_airline();
    cout << "average_flight_cost: " << fixed << setprecision(2) << average_cost << endl;
    cout << "min_flight_cost: " << fixed << setprecision(2) << min_cost << endl;
    cout << "max_flight_cost: " << fixed << setprecision(2) << max_cost << endl;
    cout << "most_popular_destination: " << most_popular_destination << endl;
    cout << "top_airlines:";
    for(int i=0; i<top_airline.size() ;i++){
        cout <<" " <<top_airline[i];
    } 
    cout <<endl;
}

vector<string> Utravel::top3_airline(){
    vector<airlines> airline_counter;
    bool found=false;
    for(int i=0;i<flights.size() ;i++){
        found=false;
        for(int j=0;j<airline_counter.size();j++){
            if(airline_counter[j].airline==flights[i].get_airline()){
                found = true;
                airline_counter[j].count += flights[i].get_num_of_sold_seats();
                break;
            }
        }
        if(found == false){
            airlines new_airline;
            new_airline.airline = flights[i].get_airline();
            new_airline.count = flights[i].get_num_of_sold_seats();
            airline_counter.push_back(new_airline);
        }
    }
    sort(airline_counter.begin(), airline_counter.end() , compare_count);
    vector<string> top_airlines;
    if(airline_counter[2].count > 0){
        top_airlines.push_back(airline_counter[0].airline);
        top_airlines.push_back(airline_counter[1].airline);
        top_airlines.push_back(airline_counter[2].airline);
        return top_airlines;        
    }
    if(airline_counter[1].count > 0){
        top_airlines.push_back(airline_counter[0].airline);
        top_airlines.push_back(airline_counter[1].airline);
        return top_airlines;        
    }
    top_airlines.push_back(airline_counter[0].airline);
    return top_airlines;        
}

string Utravel::most_popular_dest(){
    vector<string> dest;
    vector<int> count;
    bool found=false;
    for(int i=0;i<flights.size() ;i++){
        found=false;
        for(int j=0;j<dest.size();j++){
            if(dest[j]==flights[i].get_dest()){
                found = true;
                count[j] += flights[i].get_num_of_sold_seats();
                break;
            }
        }
        if(found == false){
            dest.push_back(flights[i].get_dest());
            count.push_back(flights[i].get_num_of_sold_seats());
        }
    }
    int max = count[0];
    int id=0;
    for(int i=0; i<count.size() ; i++){
        if(count[i]>max){
            max=count[i];
            id=i;
        }
    }
    return dest[id];
}

double Utravel::max_flight_cost(){
    double max_price = flights[0].total_costs(1 ,"economy");
    for(int i=0 ;i<flights.size() ;i++){
        if(flights[i].has_enough_quantity("economy",1) | flights[i].has_enough_quantity("business",1)){
            if(flights[i].total_costs(1 ,"economy") > max_price ){
                max_price = flights[i].total_costs(1 ,"economy");
            }
        }
    }
    return max_price;    
}

double Utravel::min_flight_cost(){
    double min_price = flights[0].total_costs(1 ,"economy");
    for(int i=0 ;i<flights.size() ;i++){
        if(flights[i].has_enough_quantity("economy",1) | flights[i].has_enough_quantity("business",1)){
            if(flights[i].total_costs(1 ,"economy") < min_price ){
                min_price = flights[i].total_costs(1 ,"economy");
            }
        }
    }
    return min_price;
}

double Utravel::average_flight_cost(){
    int flight_count=0;
    double total_cost=0;
    for(int i=0 ;i<flights.size() ;i++){
        if(flights[i].has_enough_quantity("economy",1) | flights[i].has_enough_quantity("business",1)){
            flight_count++;
            total_cost += flights[i].total_costs(1 ,"economy");
        }
    }
    return (double)total_cost/(double)flight_count;
}

void Utravel::cheapest_flight(stringstream& lineStream){
    string input ,date;
    string origin , dest;
    int departure_date;
    int id;
    int i=0;
    while (i<3)
    {
        getline(lineStream,input,Delimeter);
        if(input == "from"){
            getline(lineStream,origin,Delimeter);
            i++;
        }
        if(input == "to"){
            getline(lineStream,dest,Delimeter);
            i++;
        }
        if(input == "departure_date"){
            getline(lineStream,date,Delimeter);
            istringstream(date) >> departure_date;
            i++; 
        }
        if(input != "from" & input != "to" & input != "departure_date"){
            cout << "Bad Request" << endl;
            return;
        }
    }
    vector<Flight*> direct=find_direct_flights(origin,dest,departure_date);
    vector<Flight*> connecting=find_connecting_flights(origin , dest);
    int connecting_count = connecting.size();
    int direct_count = direct.size();
    if(connecting_count + direct_count == 0){
        cout << "Not Found" << endl;
        return;
    }
    find_and_show_cheapest(connecting ,direct ,connecting_count ,direct_count);
}

vector<Flight*> Utravel::find_direct_flights(string origin ,string dest,int departure_date){
    vector<Flight*> direct;
    for(int i=0;i<flights.size() ;i++){
        if(flights[i].is_origin_and_dest_the_same(origin ,dest) & flights[i].is_in_this_time(departure_date)){
            direct.push_back(&flights[i]);
        }
    }
    return direct;
}

vector<Flight*> Utravel::find_connecting_flights(string origin ,string dest ,int departure_date){
    vector<Flight*> connect;
    for(int i=0 ; i<flights.size() ;i++){
        if( flights[i].get_origin() == origin & flights[i].is_in_this_time(departure_date)){
            for(int j=0 ; j<flights.size() ;j++){
                if(flights[i].Is_connected(flights[j] , dest)){
                    connect.push_back(&flights[i]);
                    connect.push_back(&flights[j]);
                }
            }
        }
    }

    return connect;
}

void Utravel::find_and_show_cheapest(vector<Flight*> connecting , vector<Flight*> direct ,int connecting_count , int direct_count){
    int min_price_direct;
    int id_direct = 0;
    int min_price_connecting;
    int id_connecting = 0;
    if(direct_count >0){
        int min_price_direct = direct[0]->get_economy_cost();
        int id_direct = 0;
        for(int i=0; i< direct.size() ; i++){
            if(direct[i]->get_economy_cost() < min_price_direct){
                min_price_direct = direct[i]->get_economy_cost();
                id_direct = i;
            }
        }
    }
    if(connecting_count >0){
        min_price_connecting = connecting[0]->get_connecting_cost(connecting[1]);
        for(int i=0; i< connecting.size()/2 ; i++){
            if(connecting[i]->get_connecting_cost(connecting[i+1]) < min_price_connecting){
                min_price_connecting = connecting[i]->get_connecting_cost(connecting[i+1]);
                id_connecting = i;
            }
        } 
    }
    int count=0;
    if(connecting_count >0 & direct_count ==0){
        connecting[id_connecting]->show_info(count);
        connecting[id_connecting+1]->show_info(count);
        cout << "Total cost: ";
        connecting[id_connecting]->calculate_show_cost(connecting[id_connecting+1]);
        cout << endl;
    }
    if(connecting_count ==0 & direct_count >0){
        direct[id_direct]->show_info(count);
        cout << "Total cost: ";
        direct[id_direct]->show_costs(1,"economy");
    }    
    else{
        if(min_price_direct < min_price_connecting){
            direct[id_direct]->show_info(count);
            cout << "Total cost: ";
            direct[id_direct]->show_costs(1,"economy");
        }  
        if(min_price_direct > min_price_connecting){
            connecting[id_connecting]->show_info(count);
            connecting[id_connecting+1]->show_info(count);
            cout << "Total cost: ";
            connecting[id_connecting]->calculate_show_cost(connecting[id_connecting+1]);
            cout << endl;
        } 
    }
}

void Utravel::connecting_flights(stringstream& lineStream){
    string input ;
    string origin , dest;
    int id;
    int i=0;
    while (i<2)
    {
        getline(lineStream,input,Delimeter);
        if(input == "from"){
            getline(lineStream,origin,Delimeter);
            i++;
        }
        if(input == "to"){
            getline(lineStream,dest,Delimeter);
            i++;
        }
        if(input != "from" & input != "to"){
            cout << "Bad Request" << endl;
            return;
        }
    }
    vector<Flight*> connecting=find_connecting_flights(origin , dest);
    if(connecting.size()==0){
        cout << "Not Found" << endl;
        return;
    }
    int count=0;
    for(int i=0; i<connecting.size()/2 ; i++){
        cout << "Flight 1: ";
        connecting[2*i]->show_info(count);
        cout << "Flight 2: ";
        connecting[2*i+1]->show_info(count);   
        cout << "* Connection duration: ";
        connecting[2*i]->calculate_show_duration(connecting[2*i+1]);
        cout << ", Total cost: ";
        connecting[2*i]->calculate_show_cost(connecting[2*i+1]);
        cout << endl;
        cout << "----------"<< endl;
    }
}

vector<Flight*> Utravel::find_connecting_flights(string origin ,string dest){
    vector<Flight*> connect;
    for(int i=0 ; i<flights.size() ;i++){
        if( flights[i].get_origin() == origin){
            for(int j=0 ; j<flights.size() ;j++){
                if(flights[i].Is_connected(flights[j] , dest)){
                    connect.push_back(&flights[i]);
                    connect.push_back(&flights[j]);
                }
            }
        }
    }
    int count=0;
    /*for(int i=0 ;i< connect.size() ;i++){
        connect[i]->show_info(count);
    }*/
    return connect;
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

