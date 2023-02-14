#include <iostream>
#include <vector>

#include "QuizHandler.hpp"

using namespace std;

int main(int argc, char** argv) {
    QuizHandler quizHandler = QuizHandler(argv[1]);
    quizHandler.start();
    return 0;
}