#include "SingleAnswerMultipleChoiceQuestion.hpp"

using namespace std;

SingleAnswerMultipleChoiceQuestion::SingleAnswerMultipleChoiceQuestion(size_t id, std::string question, std::vector<std::string> choices, size_t correct_answer_id) :
    Question(id, question)
{
    this->choices = choices;
    this->correct_answer_id = correct_answer_id;
}

bool SingleAnswerMultipleChoiceQuestion::check_answer_matches()
{
    return answer_id == correct_answer_id;
}

string SingleAnswerMultipleChoiceQuestion::correct_answer_to_string()
{
    return to_string(correct_answer_id);
}

string SingleAnswerMultipleChoiceQuestion::answer_to_string()
{
    return to_string(answer_id);
}

void SingleAnswerMultipleChoiceQuestion::set_answer(std::string line)
{
    answer_id = stoi(line);
}

bool SingleAnswerMultipleChoiceQuestion::is_answered()
{
    return answer_id != 0;
}