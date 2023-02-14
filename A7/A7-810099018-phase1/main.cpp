#include "utravel.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

int main(int argc, char* argv[]){
    string filename=argv[1];
    Utravel travelAgency;
    travelAgency.add_flight(filename);
    travelAgency.commands();
}