#include "quiz.hpp"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[]){
    string filename=argv[1];
    quiz QuizElearn;
    QuizElearn.add_questions(filename);
    QuizElearn.get_command();
}