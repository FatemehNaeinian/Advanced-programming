#ifndef SINGLE_ANSWER_MULTIPLE_CHOICE_QUESTION_HPP
#define SINGLE_ANSWER_MULTIPLE_CHOICE_QUESTION_HPP

#include <vector>

#include "Question.hpp"

class SingleAnswerMultipleChoiceQuestion : public Question
{
public:
    SingleAnswerMultipleChoiceQuestion(size_t id, std::string question, std::vector<std::string> choices, size_t correct_answer_id);

    void set_answer(std::string line);

    std::string correct_answer_to_string();
    std::string answer_to_string();

    bool check_answer_matches();
    bool is_answered();

private:
    std::vector<std::string> choices;
    size_t correct_answer_id;
    size_t answer_id = 0;
};

#endif