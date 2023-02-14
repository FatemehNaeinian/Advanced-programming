#include "quiz.hpp"
#include "answer.hpp"
#include "questions.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;
void quiz::add_questions(string filename){
    ifstream inputFile;
    inputFile.open(filename);
    if(!inputFile.is_open()){
        cerr << "failed in opening file "<<filename<<endl;
        return ;
    }
    int Num=1;
    while(inputFile.good()){
        string line,temp;
        getline(inputFile,line);
        if(line=="single_answer"){
            getline(inputFile,line);
            string Q=line;
            getline(inputFile,line);
            int count = stoi(line);
            vector<string> chooices;
            for(int i=0; i<count ; i++){
                getline(inputFile,line);
                chooices.push_back(line);
            }
            getline(inputFile,line);
            string answer=line;
            singleQuestions.push_back(singleQ(Q , count , Num , chooices , answer));
            Num++;
        }
        if(line=="multiple_answer"){ 
            getline(inputFile,line);
            string Q=line;
            getline(inputFile,line);
            int count = stoi(line);
            vector<string> chooices;
            for(int i=0; i<count ; i++){
                getline(inputFile,line);
                chooices.push_back(line);
            }
            getline(inputFile,line);
            stringstream lineStream(line);
            vector<string> answer;
            while(getline(lineStream,temp,' ')){
                answer.push_back(temp);
            }
            multipleQuestions.push_back(multipleQ(Q , count , Num , chooices , answer));
            Num++;
        }
        if(line=="short_answer"){
            getline(inputFile,line);
            string Q=line;
            getline(inputFile,line);
            string answer=line;
            shortQuestions.push_back(shortQ(Q , Num , answer));
            Num++;
        }
    }
}


void quiz::get_command(){
    int NumOfQ=singleQuestions.size()+multipleQuestions.size()+shortQuestions.size();
    string command;
    cin>>command;
    while(true){
        if(command=="submit_answer"){
            int Num;
            cin>>Num;
            vector<string> answers;
            string answeri;
            while (true)
            {
                cin>>answeri;
                if((answeri!="submit_answer") && (answeri!="finish_exam")){
                    answers.push_back(answeri);
                }
                if((answeri=="submit_answer") || (answeri=="finish_exam")){
                    break;
                }
            }
            command=answeri;
            answersQuiz.push_back(answer(Num ,answers));
            correct(answersQuiz.size()-1);
            answersQuiz[answersQuiz.size()-1].show_result();
        }
        if(command=="finish_exam" || (answersQuiz.size()==NumOfQ)){
            finish();
            break;
        }
    }
}

void quiz::correct(int QAnswer){
    for(int j=0 ; j<singleQuestions.size(); j++){
        IscorrectSingleQ(QAnswer , j);
    }
    for(int j=0 ; j<multipleQuestions.size(); j++){
        IscorrectMultipleQ(QAnswer , j);
    }
    for(int j=0 ; j<shortQuestions.size(); j++){
        IscorrectShortQ( QAnswer , j);
    }
}

void quiz::IscorrectSingleQ(int QAnswer , int Q){
    if(singleQuestions[Q].get_Num()==answersQuiz[QAnswer].get_QNum()){
        vector<string> answerQS=answersQuiz[QAnswer].get_answers();
        if(singleQuestions[Q].get_answer()==answerQS[0]){
            answersQuiz[QAnswer].correctAnswer("correct");
        }
        else{
            answersQuiz[QAnswer].correctAnswer("wrong");
        }
        return;
    }
}

void quiz::IscorrectMultipleQ(int QAnswer , int Q){
    if(multipleQuestions[Q].get_Num()==answersQuiz[QAnswer].get_QNum()){
        vector<string> answerQS=answersQuiz[QAnswer].get_answers();
        vector<string> correctAnswers=multipleQuestions[Q].get_answer();
        if(answerQS.size()!=correctAnswers.size()){
            answersQuiz[QAnswer].correctAnswer("wrong");
            return;
        }
        if(AreEqual(answerQS,correctAnswers)){
            answersQuiz[QAnswer].correctAnswer("correct");
        }
        else{
            answersQuiz[QAnswer].correctAnswer("wrong");
        }
        return;
    }
}

void quiz::IscorrectShortQ(int QAnswer , int Q){
    if(shortQuestions[Q].get_Num()==answersQuiz[QAnswer].get_QNum()){
        vector<string> answerQS=answersQuiz[QAnswer].get_answers();
        if(shortQuestions[Q].get_answer()==answerQS[0]){
            answersQuiz[QAnswer].correctAnswer("correct");
        }
        else{
            answersQuiz[QAnswer].correctAnswer("wrong");
        }
        return;
    }
}

bool quiz::AreEqual(vector<string> answerQS,vector<string>correctAnswers){
    int count;
    for(int i=0;i<answerQS.size();i++){
        for(int j=0;j<correctAnswers.size();j++){
            if(answerQS[i]==correctAnswers[j]){
                count++;
                break;
            }
        }
    }
    if(count==correctAnswers.size()){
        return true;
    }
    return false;
}

void quiz::finish(){
    int NumOfQ=singleQuestions.size()+multipleQuestions.size()+shortQuestions.size();
    int correctAns=0;
    int findAns=0;
    question* Q;
    answer* Ans;
    for(int i=1 ;i<NumOfQ+1 ;i++){
        Q=find_question(i);
        for(int j=0;j<answersQuiz.size();j++){
            if(answersQuiz[j].get_QNum()==i){
                Ans=&answersQuiz[j];
                findAns++;
                break;
            }
        }
        if(findAns==1){
            if(Ans->get_IsCorrect()=="correct"){
                cout << i << " " << "correct" << endl;
                correctAns++;
            }
            if(Ans->get_IsCorrect()=="wrong"){
                cout << i << " " << "wrong | correct answer: "<< Q->show_answer() << ", your answer: "<< Ans->show_answer() <<endl;
            }           
        }
        if(findAns==0){
            cout << i << " no_answer | correct answer: " << Q->show_answer() <<endl;
        }
        findAns=0;
    }
    float grade = (float)correctAns / (float)NumOfQ *100;
    cout << "final grade: " << fixed << setprecision(1) << grade <<endl;
}

question* quiz::find_question(int NumQ){
    for(int j=0;j<singleQuestions.size();j++){
        if(singleQuestions[j].get_Num()==NumQ){
            return &singleQuestions[j];
        }
    }

    for(int j=0;j<multipleQuestions.size();j++){
        if(multipleQuestions[j].get_Num()==NumQ){
            return &multipleQuestions[j];
        }
    }       

    for(int j=0;j<shortQuestions.size();j++){
        if(shortQuestions[j].get_Num()==NumQ){
            return &shortQuestions[j];
        }
    } 
}