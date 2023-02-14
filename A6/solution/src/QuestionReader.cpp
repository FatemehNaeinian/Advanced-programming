#include "QuestionReader.hpp"

using namespace std;

QuestionReader::QuestionReader(string questions_file_path)
{
    this->questions_file_path = questions_file_path;
    this->current_id = 1;
}

std::vector<Question*> QuestionReader::read_questions()
{
    ifstream file(questions_file_path);
    vector<Question*> questions;
    while (file.eof() == false)
    {
        questions.push_back(read_question(file));
        string temp_sign;
        getline(file, temp_sign);
        current_id++;
    }
    return questions;
}

Question* QuestionReader::read_question(std::ifstream& f)
{
    
    string question_type;
    getline(f, question_type);
    if (question_type == "short_answer")
        return read_short_answer_question(f);
    else if (question_type == "single_answer")
        return read_single_answer_multiple_choice_question(f);
    else if (question_type == "multiple_answer")
        return read_multiple_answer_multiple_choice_question(f);
    else
        throw "Invalid question type";
    
}

ShortAnswerQuestion* QuestionReader::read_short_answer_question(ifstream& f)
{
    string question;
    getline(f, question);
    string correct_answer;
    getline(f, correct_answer);
    return new ShortAnswerQuestion(current_id, question, correct_answer);
}

SingleAnswerMultipleChoiceQuestion* QuestionReader::read_single_answer_multiple_choice_question(std::ifstream& f)
{
    string question;
    getline(f, question);
    string choices_count;
    getline(f, choices_count);
    size_t choices_count_int = stoi(choices_count);
    vector<string> choices;
    for (size_t i = 0; i < choices_count_int; i++)
    {
        string choice;
        getline(f, choice);
        choices.push_back(choice);
    }
    string correct_answer_input;
    getline(f, correct_answer_input);
    return new SingleAnswerMultipleChoiceQuestion(current_id, question, choices, stoi(correct_answer_input));
}

MultipleAnswerMultipleChoiceQuestion* QuestionReader::read_multiple_answer_multiple_choice_question(std::ifstream& f)
{
    string question;
    getline(f, question);
    string choices_count;
    getline(f, choices_count);
    size_t choices_count_int = stoi(choices_count);
    vector<string> choices;
    for (size_t i = 0; i < choices_count_int; i++)
    {
        string choice;
        getline(f, choice);
        choices.push_back(choice);
    }
    string correct_answers_input;
    getline(f, correct_answers_input);
    vector<size_t> correct_answers;
    stringstream ss(correct_answers_input);
    string correct_answer;
    while (getline(ss, correct_answer, ' '))
    {
        correct_answers.push_back(stoi(correct_answer));
    }
    return new MultipleAnswerMultipleChoiceQuestion(current_id, question, choices, correct_answers);
}