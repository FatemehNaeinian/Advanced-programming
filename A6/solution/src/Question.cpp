#include "Question.hpp"

using namespace std;

Question::Question(size_t id, string question)
{
    this->id = id;
    this->question = question;
}

size_t Question::get_id()
{
    return id;
}