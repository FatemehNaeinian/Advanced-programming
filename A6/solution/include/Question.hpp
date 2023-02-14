#ifndef QUESTION_HPP
#define QUESTION_HPP

#include <iostream>

class Question
{
public:
    Question(size_t id, std::string question);

    size_t get_id();
    virtual std::string correct_answer_to_string() = 0;
    virtual std::string answer_to_string() = 0;
    virtual void set_answer(std::string answer_line) = 0;
    virtual bool check_answer_matches() = 0;
    virtual bool is_answered() = 0;

protected:
    size_t id;
    std::string question;
};

#endif