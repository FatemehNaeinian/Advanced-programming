#ifndef QUESTION_READER_HPP
#define QUESTION_READER_HPP

#include <string>
#include <fstream>
#include <sstream>

#include "Question.hpp"
#include "ShortAnswerQuestion.hpp"
#include "SingleAnswerMultipleChoiceQuestion.hpp"
#include "MultipleAnswerMultipleChoiceQuestion.hpp"

class QuestionReader
{
public:
    QuestionReader(std::string questions_file_path);
    std::vector<Question*> read_questions();

private:
    size_t current_id;
    std::string questions_file_path;

    Question* read_question(std::ifstream& f);
    ShortAnswerQuestion* read_short_answer_question(std::ifstream& f);
    SingleAnswerMultipleChoiceQuestion* read_single_answer_multiple_choice_question(std::ifstream& f);
    MultipleAnswerMultipleChoiceQuestion* read_multiple_answer_multiple_choice_question(std::ifstream& f);
};

#endif