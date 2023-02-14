#ifndef comp_H
#define comp_H "comp_H"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct airlines
{
    string airline;
    int count;
};

bool compare_count(airlines a , airlines b );
#endif