
#ifndef INPUT_H
#define INPUT_H "INPUT_H"
#include "Ball.hpp"
#include "playground.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

vector<string> read_file(string filename);
void apply_input_ball(vector<string> fileToString,Ball& ball);
void apply_input_window(vector<string> fileToString,vector<int>&window_size);
void apply_input_playground(vector<string> fileToString,Playground &playgrounds);
#endif
