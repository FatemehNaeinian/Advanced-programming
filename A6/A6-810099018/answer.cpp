#include "answer.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <sstream>

using namespace std;

answer::answer(int Num , vector<string> answer_){
    QNum=Num;
    answers=answer_;
    IsCorrect=" ";
}

void answer::correctAnswer(string status){
    IsCorrect=status;
}

int answer::get_QNum(){return QNum;}

vector<string> answer::get_answers(){return answers;}

void answer::show_result(){
    cout << IsCorrect <<" answer."<<endl;
}

string answer::get_IsCorrect(){
    return IsCorrect;
}

string answer::show_answer(){
       ostringstream Qanswer;
    if(!answers.empty()){
        copy(answers.begin() , answers.end()-1 , ostream_iterator <string>(Qanswer, " "));
        Qanswer << answers.back();
    }
    return Qanswer.str();
}