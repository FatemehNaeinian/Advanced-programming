#ifndef QUIZ_HANDLER_HPP
#define QUIZ_HANDLER_HPP

#include <vector>
#include <iomanip>

#include "Question.hpp"
#include "QuestionReader.hpp"

class QuizHandler {
public:
    QuizHandler(std::string question_file_path);
    void start();

private:
    bool is_ended();
    double get_score();
    void show_exam_report();

    std::vector<Question*> questions;
};

#endif