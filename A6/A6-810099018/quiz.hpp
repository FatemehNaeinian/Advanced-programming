#ifndef quiz_H
#define quiz_H "quiz_H"
#include "answer.hpp"
#include "questions.hpp"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class quiz{
public:
    void add_questions(string filename);
    void get_command();
    void correct(int QAnswer);
    bool AreEqual(vector<string> answerQS,vector<string>correctAnswers);
    void finish();
    question* find_question(int NumQ);
    void IscorrectSingleQ(int QAnswer , int Q);
    void IscorrectMultipleQ(int QAnswer , int Q);
    void IscorrectShortQ(int QAnswer , int Q);
private:
    vector<shortQ> shortQuestions;
    vector<singleQ> singleQuestions;
    vector<multipleQ> multipleQuestions;
    vector<answer> answersQuiz;
};

#endif