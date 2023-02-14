#include "questions.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <sstream>
using namespace std;

question::question(int Num_ , string Q_){
    Num=Num_;
    QuizQuestion=Q_;
}

int question::get_Num(){return Num;}

string question::get_question(){return QuizQuestion;}


singleQ::singleQ(string question_ ,int count_ , int Num_ , vector<string> choices_ ,string answer_ )
        :question(Num_ , question_ )
{
    choiceCount=count_;
    choices=choices_ ;
    answer=answer_ ;
}


multipleQ::multipleQ(string question_ ,int count_ , int Num_ , vector<string> choices_ ,vector<string> answer_ )
        :question(Num_ , question_ )
{
    choiceCount=count_;
    choices=choices_ ;
    answer=answer_ ;
}

shortQ::shortQ(string question_ , int Num_ , string answer_ )
        :question(Num_ , question_ )
{
    answer=answer_;
}


string singleQ::get_answer(){return answer;}

vector<string> multipleQ::get_answer(){return answer;}

string shortQ::get_answer(){return answer;}

string question::show_answer(){
    return "failed";
}

string singleQ::show_answer(){
    return answer;
}

string multipleQ::show_answer(){
    ostringstream Qanswer;
    if(!answer.empty()){
        copy(answer.begin() , answer.end()-1 , ostream_iterator <string>(Qanswer, " "));
        Qanswer << answer.back();
    }
    return Qanswer.str();
}

string shortQ::show_answer(){
    return answer;
}