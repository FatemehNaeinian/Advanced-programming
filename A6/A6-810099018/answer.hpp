#ifndef A_H
#define A_H "A_H"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class answer{
public:
    answer(int Num , vector<string> answer_);
    void correctAnswer(string status);
    int get_QNum();
    vector<string> get_answers();
    void show_result();
    string get_IsCorrect();
    string show_answer();
private:
    int QNum;
    vector<string> answers;
    string IsCorrect;
};

#endif