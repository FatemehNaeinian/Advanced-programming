#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;
void GettingParticipants(vector<string>& participants);
void MakingVoteTable(vector<string>& participants,vector<vector<string>>& Periods,int NumOfPeriod);
void GettingVote(vector<string>& Votes);
void ApplyVotes(vector<vector<string>>& Periods,vector<string>& Votes,int NumOfPeriod,int NumOfParticipants);
void CountPeriodsVotes(vector<vector<string>>& Periods,int NumOfPeriod,vector<int>& NOvote,vector<int>& IF_NECESSARYvote);
void FindBestPeriod(vector<int>& NOvote,vector<int>& IF_NECESSARYvote,vector<int>&BestPeriods,int NumOfParticipants);
void ShowResult(vector<int>&BestPeriods,vector<vector<string>>&Periods);
void PrintNames(vector<vector<string>>&Periods,int BestPeriods,string stringCompare);

int main(){
    int NumOfPeriod;
    string Numstring;
    getline(cin , Numstring);
    NumOfPeriod=stoi(Numstring);
    vector<string> participants;
    GettingParticipants(participants);
    int NumOfParticipants=participants.size();
    vector<vector<string>> Votes(NumOfParticipants);
    vector<vector<string>> Periods(NumOfPeriod);
    MakingVoteTable(participants,Periods,NumOfPeriod);
    for(int i=0;i<NumOfParticipants;i++){
        GettingVote(Votes[i]);
        ApplyVotes(Periods,Votes[i],NumOfPeriod,NumOfParticipants);
    }
    vector<int> NOvote;
    vector<int> IF_NECESSARYvote;
    CountPeriodsVotes(Periods,NumOfPeriod,NOvote,IF_NECESSARYvote);
    vector<int> BestPeriods;
    FindBestPeriod(NOvote,IF_NECESSARYvote,BestPeriods,NumOfParticipants);
    ShowResult(BestPeriods,Periods);
}

void GettingParticipants(vector<string>& participants){
    string InputLine ;  
    getline(cin,InputLine);
    const char delimit = ' ';            
    stringstream LineStream(InputLine);             
    string EachParticipant;  
    while (getline (LineStream, EachParticipant, delimit) )  
    {  
        participants.push_back(EachParticipant); 
    }  
}

void MakingVoteTable(vector<string>& participants,vector<vector<string>>& Periods,int NumOfPeriod){
    for(int u=0;u<participants.size();u++){
        for(int y=0;y<NumOfPeriod;y++){
             Periods[y].push_back(participants[u]);
            Periods[y].push_back("IF_NECESSARY");     
        }       
    }
}

void GettingVote(vector<string>& Votes){
    string InputLine;
    getline(cin,InputLine);
    char delimit = ':';  
    stringstream LineStream(InputLine);
    string vote;
    getline(LineStream,vote,delimit);
    Votes.push_back(vote);
    delimit = '|'; 
    while (getline (LineStream, vote, delimit) )  
    {  
        Votes.push_back(vote); 
    }  
}

void ApplyVotes(vector<vector<string>>& Periods,vector<string>& Votes,int NumOfPeriod,int NumOfParticipants){
    int turn;
    for(int r=0;r<NumOfParticipants;r++){
        if(Votes[0].compare(Periods[0][2*r])==0){
            turn=r;
            break;
        }
    }
    const char delimit = ' ';
    for(int j=1;j<Votes.size() ;j++){
    stringstream StringStream(Votes[j]); 
    string voteandperiod; 
    getline (StringStream,voteandperiod, delimit);
    int voteperiod=stoi(voteandperiod);
    getline (StringStream,voteandperiod, delimit);
    Periods[voteperiod].at(2*turn+1)=voteandperiod;
    }
}

void CountPeriodsVotes(vector<vector<string>>& Periods,int NumOfPeriod,vector<int>& NOvote,vector<int>& IF_NECESSARYvote){
    string No="NO";
    string IF_NECESSARY="IF_NECESSARY";
    int NumOfNo=0;
    int NumOfNecessary=0;
    for(int j=0;j<NumOfPeriod;j++){
        NumOfNo=0;
        NumOfNecessary=0;
        for(int t=0;t<Periods[j].size()/2;t++ ){
            if(No.compare(Periods[j][2*t+1])==0){
                NumOfNo++;
            }
            if(IF_NECESSARY.compare(Periods[j][2*t+1])==0){
                NumOfNecessary++;
            }            
        }
        NOvote.push_back(NumOfNo);
        IF_NECESSARYvote.push_back(NumOfNecessary);
    }
}

void FindBestPeriod(vector<int>& NOvote,vector<int>& IF_NECESSARYvote,vector<int>&BestPeriods,int NumOfParticipants){
    vector<vector<int>> FindLessNo(3);
    int NumOfSelectedPeriodsInLoop=0;
    int periodsCount=0;
    int equals=0;
    for(int Num=0;Num<NumOfParticipants;Num++){
        NumOfSelectedPeriodsInLoop=0;
        for(int current=0;current<NOvote.size();current++){
            if(NOvote[current]==Num){
                FindLessNo[equals].push_back(current);
                NumOfSelectedPeriodsInLoop++;
                periodsCount++;
            }
        }
        if(NumOfSelectedPeriodsInLoop>0){
            equals++;
        }
        if(periodsCount>=3){
            break;
        }
    }  
    int CountBests=0;
    for(int i=0;i<equals;i++){
        for(int m=0;m<FindLessNo[i].size();m++){
            for(int Num2=0;Num2<=NumOfParticipants;Num2++){
                if(IF_NECESSARYvote[FindLessNo[i][m]]==Num2){
                    BestPeriods.push_back(FindLessNo[i][m]);
                    CountBests++;
               }
               if(CountBests>=3){
                   break;
               }
            }
        }
    }
}

void ShowResult(vector<int>&BestPeriods,vector<vector<string>>&Periods){
    string yes="YES";
    string no="NO";
    string if_necessary="IF_NECESSARY";
    for(int i=0;i<BestPeriods.size();i++){
        cout<<"Time slot "<<BestPeriods[i]<<":"<<endl;
        cout<<"YES:";
        PrintNames(Periods,BestPeriods[i],yes);
        cout<<"NO:";
        PrintNames(Periods,BestPeriods[i],no);
        cout<<"IF_NECESSARY:";
        PrintNames(Periods,BestPeriods[i],if_necessary); 
        cout<<"###"<<endl;               
    }
}

void PrintNames(vector<vector<string>>&Periods,int BestPeriods,string stringCompare){
    for(int u=0;u<Periods[0].size()/2;u++){
        if(stringCompare.compare(Periods[BestPeriods][2*u+1])==0){
            cout<<" "<<Periods[BestPeriods][2*u];
        }
    }
    cout<<"\n";
}