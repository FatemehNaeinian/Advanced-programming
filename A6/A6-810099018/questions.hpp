#ifndef Q_H
#define Q_H "Q_H"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>
using namespace std;


class question{
public:
    question(int Num_ , string Q_);
    int get_Num();
    string get_question();
    virtual string show_answer();
private:
    int Num;
    string QuizQuestion;
};

class singleQ : public question{
public:
    singleQ(string question_ ,int count_ , int Num_ , vector<string> choices_ ,string answer_ );
    string get_answer();
    virtual string show_answer();
private:
    int choiceCount;
    vector<string> choices;
    string answer;
};

class multipleQ : public question{
public:
    multipleQ (string question_ ,int count_ , int Num_ , vector<string> choices_ ,vector<string> answer_ );
    vector<string> get_answer();
    virtual string show_answer();
private:
    int choiceCount;
    vector<string> choices;
    vector<string> answer;

};

class shortQ : public question{
public:
    shortQ(string question_ , int Num_ , string answer_ );
    string get_answer();
    virtual string show_answer();
private:
    string answer;
};
#endif