#include "Ball.hpp"
#include "playground.hpp"
#include "readinput.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;
const char delim = ' ';

vector<string> read_file(string filename){
    vector<string> fileToString;
    ifstream inputFile;
    inputFile.open(filename);
    if(!inputFile.is_open()){
        cerr << "failed in opening file "<<filename<<endl;
        return fileToString;
    }
    while(inputFile.good()){
        string line,temp;
        getline(inputFile,line);
        stringstream lineStream(line);
        while(getline(lineStream,temp,delim)){
            fileToString.push_back(temp);
        }
    }
    return fileToString;
}

void apply_input_ball(vector<string> fileToString,Ball& ball){
    for(int i=0; i<fileToString.size();i++){
        if(fileToString[i]=="ball"){
            ball.initialize(stoi(fileToString[i+1]),stoi(fileToString[i+2]));
            return;
        }
    }
    return ;
}

void apply_input_window(vector<string> fileToString,vector<int>&windowsize){
    for(int i=0; i<fileToString.size();i++){
        if(fileToString[i]=="window_size"){
            windowsize.push_back(stoi(fileToString[i+1]));
            windowsize.push_back(stoi(fileToString[i+2]));
            return;
        }
    }
    return;
}

void apply_input_playground(vector<string> fileToString,Playground& playgrounds){
    for(int i=0; i<fileToString.size();i++){
        if(fileToString[i]=="wall"){
            playgrounds.add_wall(Rectangle(stoi(fileToString[i+1]),stoi(fileToString[i+2]),stoi(fileToString[i+3]),stoi(fileToString[i+4])));
        }
        if(fileToString[i]=="sharp_wall"){
            playgrounds.add_sharp_wall(Rectangle(stoi(fileToString[i+1]),stoi(fileToString[i+2]),stoi(fileToString[i+3]),stoi(fileToString[i+4])));
        }
        if(fileToString[i]=="normal_area"){
           playgrounds.add_normal_area(Rectangle(stoi(fileToString[i+1]),stoi(fileToString[i+2]),stoi(fileToString[i+3]),stoi(fileToString[i+4])));
        }
        if(fileToString[i]=="water_area"){
            playgrounds.add_water_area(Rectangle(stoi(fileToString[i+1]),stoi(fileToString[i+2]),stoi(fileToString[i+3]),stoi(fileToString[i+4])));
        }
        if(fileToString[i]=="sand_area"){
            playgrounds.add_sand_area(Rectangle(stoi(fileToString[i+1]),stoi(fileToString[i+2]),stoi(fileToString[i+3]),stoi(fileToString[i+4])));
        }
        if(fileToString[i]=="hole"){
             playgrounds.add_hole(Point(stoi(fileToString[i+1]),stoi(fileToString[i+2])));
        }        
    }
}
