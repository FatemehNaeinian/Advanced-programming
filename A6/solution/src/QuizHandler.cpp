#include "QuizHandler.hpp"

using namespace std;

QuizHandler::QuizHandler(string question_file_path)
{
    QuestionReader reader = QuestionReader(question_file_path);
    questions = reader.read_questions();
}

void QuizHandler::start()
{
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        string question_id_input;
        string command_type;
        ss >> command_type;
        if (is_ended())
        {
            show_exam_report();
            break;
        }
        if (command_type == "submit_answer") {
            ss >> question_id_input;
            string answer;
            getline(ss, answer);
            size_t question_id = stoi(question_id_input);
            questions[question_id-1]->set_answer(answer);
            string answer_status = questions[question_id-1]->check_answer_matches() ? "correct" : "wrong";
            cout << answer_status << " answer." << endl;
        }
        else if (command_type == "finish_exam") {
            show_exam_report();
            break;
        }
    }
}

bool QuizHandler::is_ended()
{
    for (size_t i = 0; i < questions.size(); i++) {
        if (!questions[i]->is_answered()) {
            return false;
        }
    }
    return true;
}

void QuizHandler::show_exam_report()
{
    for (Question* question : questions){
        string answer_status;
        if (!question->is_answered()) {
            answer_status = "no_answer";
        }
        else {
            answer_status = question->check_answer_matches() ? "correct" : "wrong";
        }
        cout << question->get_id() << " " << answer_status;
        if (answer_status == "no_answer")
            cout << " | " << "correct answer: " << question->correct_answer_to_string() << endl;
        else if (answer_status == "wrong")
            cout << " | " << "correct answer: " << question->correct_answer_to_string() << ", " << "your answer: " << question->answer_to_string() << endl;
        else
            cout << endl;
    }
    cout << "final grade: " << fixed << setprecision(1) << get_score() << endl;
}

double QuizHandler::get_score()
{
    double true_answers = 0;
    for (size_t i = 0; i < questions.size(); i++){
        if (questions[i]->is_answered())
            if (questions[i]->check_answer_matches())
            true_answers += 1;
    }
    return true_answers / questions.size() * 100;
}