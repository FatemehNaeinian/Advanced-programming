#include "ShortAnswerQuestion.hpp"

using namespace std;

ShortAnswerQuestion::ShortAnswerQuestion(size_t id, string question, string correct_answer) : Question(id, question), correct_answer(correct_answer)
{
    this->correct_answer = correct_answer;
}

bool ShortAnswerQuestion::check_answer_matches()
{
    return answer == correct_answer;
}

string ShortAnswerQuestion::correct_answer_to_string()
{
    return correct_answer;
}

string ShortAnswerQuestion::answer_to_string()
{
    return answer;
}

void ShortAnswerQuestion::set_answer(string line)
{
    answer = line.substr(1, line.size());
}

bool ShortAnswerQuestion::is_answered()
{
    return answer != "";
}