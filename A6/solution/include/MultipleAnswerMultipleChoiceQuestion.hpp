#ifndef MULTIPLE_ANSWER_MULTIPLE_CHOICE_QUESTION_HPP
#define MULTIPLE_ANSWER_MULTIPLE_CHOICE_QUESTION_HPP

#include <vector>
#include <algorithm>

#include "Question.hpp"
#include "Util.hpp"

class MultipleAnswerMultipleChoiceQuestion : public Question
{
public:
    MultipleAnswerMultipleChoiceQuestion(size_t id, std::string question, std::vector<std::string> choices, std::vector<size_t> correct_answer_ids);
    bool check_answer_matches();

    std::string correct_answer_to_string();
    std::string answer_to_string();
    void set_answer(std::string line);
    bool is_correct();
    bool is_answered();

private:
    std::vector<std::string> choices;
    std::vector<size_t> correct_answer_ids;
    std::vector<size_t> answer_ids;
};

#endif