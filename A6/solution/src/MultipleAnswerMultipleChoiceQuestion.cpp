#include "MultipleAnswerMultipleChoiceQuestion.hpp"

using namespace std;

MultipleAnswerMultipleChoiceQuestion::MultipleAnswerMultipleChoiceQuestion(size_t id, std::string question, std::vector<std::string> choices, std::vector<size_t> correct_answer_ids) :
    Question(id, question)
{
    this->choices = choices;
    this->correct_answer_ids = correct_answer_ids;
}

bool MultipleAnswerMultipleChoiceQuestion::check_answer_matches()
{
    sort(answer_ids.begin(), answer_ids.end());
    sort(correct_answer_ids.begin(), correct_answer_ids.end());
    return answer_ids == correct_answer_ids;
}

string MultipleAnswerMultipleChoiceQuestion::correct_answer_to_string()
{
    string answer_string = "";
    for (size_t i = 0; i < correct_answer_ids.size(); i++)
    {
        answer_string += to_string(correct_answer_ids[i]);
        if (i != correct_answer_ids.size() - 1)
        {
            answer_string += " ";
        }
    }
    return answer_string;    
}

string MultipleAnswerMultipleChoiceQuestion::answer_to_string()
{
    string answer_string = "";
    for (size_t i = 0; i < answer_ids.size(); i++)
    {
        answer_string += to_string(answer_ids[i]);
        if (i != answer_ids.size() - 1)
        {
            answer_string += " ";
        }
    }
    return answer_string;
}

void MultipleAnswerMultipleChoiceQuestion::set_answer(std::string answer_line)
{
    answer_ids.clear();
    vector<string> answer_ids_input = Util::split_string(answer_line, ' ');
    for (size_t i = 0; i < answer_ids_input.size(); i++)
    {
        answer_ids.push_back(stoi(answer_ids_input[i]));
    }
}

bool MultipleAnswerMultipleChoiceQuestion::is_answered()
{
    return answer_ids.size() > 0;
}