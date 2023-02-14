#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

void GetInputs(vector<vector<char>>& InputWords,int&NumOfInput){
    string input;
    while(getline(cin,input)){
        vector<char> charinput(input.begin(),input.end());
        if(input=="###"){
            break;
        }
        else{
            InputWords.push_back(charinput);
            NumOfInput++;
        }
    }
    return;
}

int CountSimilarLetter(vector<char>&Words,vector<char>&Line,int Position){
    int count=0;
    for(int j=0;j<Words.size();j++){
        if(Words[j]==Line[Position+j]){
            count++;
        }
    }
    return count;
}

void SplitWords(vector<char>&splitLine,vector<vector<char>>&Words,vector<char>&Line,int NumOfWords,int Position){
    int similarLetter=0;
    if(Line.size()==Position){
        splitLine.erase(splitLine.begin()+splitLine.size()-1);
        return;
    }
    else{
        for(int n=0;n<NumOfWords;n++){
            similarLetter=0;
            if(Words[n][0]==Line[Position]){
                similarLetter=CountSimilarLetter(Words[n],Line,Position);
            }
            if(similarLetter==Words[n].size()){
                for(int i=0;i<Words[n].size();i++){
                    splitLine.push_back(Line[Position+i]);
                }
                splitLine.push_back(' ');
                Position=Position+Words[n].size();
                SplitWords(splitLine,Words,Line,NumOfWords,Position);
                if(splitLine[splitLine.size()-1]=='1'){
                    Position=Position-Words[n].size();
                    for(int i=0;i<Words[n].size()+3;i++){
                        splitLine.erase(splitLine.begin()+splitLine.size()-1);
                    }
                }
                else{
                    return ;
                }
            }
        }
        splitLine.push_back('-');
        splitLine.push_back('1');
        return;
    }
}

void FindResult(vector<vector<char>>&result,vector<vector<char>>&Words,vector<vector<char>>&Line,int NumOfLines,int NumOfWords){
    if(result.size()==NumOfLines){
        return;
    }
    else{
        vector<char> splitLine;
        int startPoint=0;
        SplitWords(splitLine,Words,Line[result.size()],NumOfWords,startPoint);
        result.push_back(splitLine);
        FindResult(result,Words,Line,NumOfLines,NumOfWords);
    }
}

void ShowResult(vector<vector<char>> result){
    for (int i = 0; i < result.size(); i++) {
        if(i!=0){
            cout<<"\n";
        }
        for (int j = 0; j < result[i].size(); j++)
            cout << result[i][j];
        cout << endl;
        cout<<"***";
    }
}

int main(){
    vector<vector<char>> Words;
    vector<vector<char>> Line;
    int NumOfWords=0;
    int NumOfLines=0;
    GetInputs(Words,NumOfWords);
    GetInputs(Line,NumOfLines);
    vector<vector<char>> result;
    FindResult(result,Words,Line,NumOfLines,NumOfWords);
    ShowResult(result);

}