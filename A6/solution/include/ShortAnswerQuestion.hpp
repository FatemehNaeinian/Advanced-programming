#ifndef SHORT_ANSWER_QUESTION_HPP
#define SHORT_ANSWER_QUESTION_HPP

#include "Question.hpp"

class ShortAnswerQuestion : public Question
{
public:
    ShortAnswerQuestion(size_t id, std::string question, std::string correct_answer);

    void set_answer(std::string line);

    std::string correct_answer_to_string();
    std::string answer_to_string();

    bool check_answer_matches();
    bool is_answered();

private:
    std::string correct_answer;
    std::string answer = "";
};

#endif