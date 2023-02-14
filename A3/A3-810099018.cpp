#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;
const char fileDelimeter=',';
const char timeDelimeter=':';

#define InfoNum 4
#define Max_Stay 60
#define Min_stay 15
#define Time_to_reach 30
#define Finish_hour 23
#define Finish_minute 16
#define One_Hour 60

struct scheduleStruct{
    string name;
    int rank;
    int openingTimeHour;
    int openingTimeMinute;
    int closingTimeHour;
    int closingTimeMinute;
};

struct outputScheduleStruct{
    string name;
    int startTimeHour;
    int startTimeMinute;
    int finishTimeHour;
    int finishTimeMinute;
};

void readInputFromFileToStringVector(vector<string>& fileToString,string filename){
    ifstream inputFile;
    inputFile.open(filename);
    if(!inputFile.is_open()){
        cerr << "failed in opening file "<<filename<<endl;
        return ;
    }
    while(inputFile.good()){
        string line,temp;
        getline(inputFile,line);
        stringstream lineStream(line);
        while(getline(lineStream,temp,fileDelimeter)){
            fileToString.push_back(temp);
        }
    }
}

void FindOrderOfInput(vector<string>& stringOfFile,int& nameNum,int& openingTimeNum,int& closingTimeNum,int& rankNum){
    for(int i=0;i<InfoNum;i++){
        if(stringOfFile[i]=="name"){
            nameNum=i;
        }
        if(stringOfFile[i]=="openingTime"){
            openingTimeNum=i;
        }
        if(stringOfFile[i]=="closingTime"){
            closingTimeNum=i;
        }
        if(stringOfFile[i]=="rank"){
            rankNum=i;
        }
    }
}

void calculateInteger(int& hour,int& minute ,string timeInput){
    string temp;
    stringstream time(timeInput);
    getline(time,temp,timeDelimeter);
    hour=stoi(temp);
    getline(time,temp,timeDelimeter);
    minute=stoi(temp);
}

void MakeStructForInputPlaces(scheduleStruct& currentPlace,string& name,int& openingTimeHour,int& openingTimeMinute,int& closingTimeHour,int& closingTimeMinute,int& rank){
    currentPlace.name=name;
    currentPlace.rank=rank;
    currentPlace.openingTimeHour=openingTimeHour;
    currentPlace.openingTimeMinute=openingTimeMinute;
    currentPlace.closingTimeHour=closingTimeHour;
    currentPlace.closingTimeMinute=closingTimeMinute;
}

void importStringVectorToStructs(vector<string>& stringOfFile,vector<scheduleStruct>& schedule){
    int nameNum,openingTimeNum,closingTimeNum,rankNum;
    FindOrderOfInput(stringOfFile,nameNum,openingTimeNum,closingTimeNum,rankNum);
    int openingTimeHour,openingTimeMinute,closingTimeHour,closingTimeMinute,rank;
    scheduleStruct currentPlace;
    for(int i=1;i<stringOfFile.size()/4;i++){
        calculateInteger(openingTimeHour,openingTimeMinute,stringOfFile[4*i+openingTimeNum]);
        calculateInteger(closingTimeHour,closingTimeMinute,stringOfFile[4*i+closingTimeNum]);
        rank=stoi(stringOfFile[4*i+rankNum]);
        MakeStructForInputPlaces(currentPlace,stringOfFile[4*i+nameNum],openingTimeHour,openingTimeMinute,closingTimeHour,closingTimeMinute,rank);
        schedule.push_back(currentPlace);
    }
}

void readInput(vector<scheduleStruct>& schedule,string& filename){
    vector<string> fileToString;
    readInputFromFileToStringVector(fileToString,filename);
    importStringVectorToStructs(fileToString,schedule);
}

bool Compare(scheduleStruct a, scheduleStruct b){
    if(a.openingTimeHour < b.openingTimeHour){
        return a.openingTimeHour < b.openingTimeHour;
    }
    if(a.openingTimeHour == b.openingTimeHour){
        if(a.openingTimeMinute == b.openingTimeMinute){
            return a.rank < b.rank;
        }
        else{
            return a.openingTimeMinute < b.openingTimeMinute;
        }
    }
    else{
        return a.openingTimeHour < b.openingTimeHour;
    }
}

void sortMyVectorOfStruct(vector<scheduleStruct>& schedule){
	sort(schedule.begin(), schedule.end(), Compare);
}

vector<int> closestTimePeriod(vector<scheduleStruct>& schedule,int timeHour,int timeMinute){
    vector<int> TurnNumOfSchedule;
    for(int i=0;i<schedule.size();i++){
        if(schedule[i].openingTimeHour<timeHour){
            if(schedule[i].closingTimeHour>timeHour){
                TurnNumOfSchedule.push_back(i);
            }
            if(schedule[i].closingTimeHour==timeHour){
                if(schedule[i].closingTimeMinute>timeMinute+Min_stay+Time_to_reach ){
                    TurnNumOfSchedule.push_back(i);
                }
            }
        }
        if(schedule[i].openingTimeHour>timeHour){
            TurnNumOfSchedule.push_back(i);
        }
        if(schedule[i].openingTimeHour==timeHour){
            if(schedule[i].openingTimeMinute>timeMinute){
                TurnNumOfSchedule.push_back(i);
            }
            if(schedule[i].openingTimeMinute<=timeMinute){
                if(schedule[i].closingTimeHour>timeHour){
                    TurnNumOfSchedule.push_back(i);
                }
                if(schedule[i].closingTimeHour==timeHour){
                    if(schedule[i].closingTimeMinute>timeMinute+Min_stay+Time_to_reach ){
                        TurnNumOfSchedule.push_back(i);
                    }
                }
            }
        }
    }
    return TurnNumOfSchedule;
}

void convert60MinutesToHour(int& timeHour,int& timeMinute){
    timeMinute=timeMinute-One_Hour;
    timeHour=timeHour+1;
}

void findNewTime(int& timeHour,int& timeMinute,int& remainMinutesToClose){
    if(remainMinutesToClose>Time_to_reach+Max_Stay){
        timeMinute=timeMinute+Time_to_reach;
        timeHour=timeHour+1;
        if(timeMinute>=One_Hour){
            convert60MinutesToHour(timeHour,timeMinute);
        }
    }
    else{
        timeMinute=timeMinute+remainMinutesToClose;
        if(timeMinute>=One_Hour){
            convert60MinutesToHour(timeHour,timeMinute);
        }
        if(timeMinute>=One_Hour){
            convert60MinutesToHour(timeHour,timeMinute);  
        }      
    }
}

void FindStartTimeToVisit(int& startTimeMinute,int& startTimeHour,int timeHour,int timeMinute,int remainMinutesToClose){
    if(remainMinutesToClose>Time_to_reach+Max_Stay){
        startTimeMinute=timeMinute+Time_to_reach;
        startTimeHour=timeHour;
        if(startTimeMinute>=One_Hour){
            convert60MinutesToHour(startTimeHour,startTimeMinute);
        }
    }
    else{
        startTimeMinute=timeMinute+Time_to_reach;
        startTimeHour=timeHour;
        if(startTimeMinute>=One_Hour){
            convert60MinutesToHour(startTimeHour,startTimeMinute);
        }
    }
}

void FindFinishTimeToVisit(int& startTimeMinute,int& startTimeHour,int& finishTimeHour,int& finishTimeMinute,int remainMinutesToClose){
    if(remainMinutesToClose>Time_to_reach+Max_Stay){
        finishTimeMinute=startTimeMinute;
        finishTimeHour=startTimeHour+1;
    }
    else{
        finishTimeMinute=startTimeMinute+remainMinutesToClose-Time_to_reach;
        finishTimeHour=startTimeHour;
        if(finishTimeMinute>=One_Hour){
            convert60MinutesToHour(finishTimeHour,finishTimeMinute);
        }
    }
}

void FindNewTimeWhenThereIsGap(int& timeHour,int& timeMinute,scheduleStruct nextPlace){
    timeHour=nextPlace.openingTimeHour;
    timeMinute=nextPlace.openingTimeMinute-Time_to_reach;
    if(timeMinute<0){
        timeMinute=timeMinute+One_Hour;
        timeHour=timeHour-1;
    }
}

void MakeNewStructForOnePlace(outputScheduleStruct& output,int& startTimeMinute,int& startTimeHour,int& finishTimeHour
,int& finishTimeMinute,string name){
    output.name=name;
    output.startTimeHour=startTimeHour;
    output.startTimeMinute=startTimeMinute;
    output.finishTimeHour=finishTimeHour;
    output.finishTimeMinute=finishTimeMinute;
}

void MakeTimetable(vector<scheduleStruct>& schedule,vector<outputScheduleStruct>& timetableOutput,int timeHour,int timeMinute){
    vector<int> ClosestPeriod;
    ClosestPeriod=closestTimePeriod(schedule,timeHour,timeMinute);
    if((timeHour>Finish_hour && timeMinute>Finish_minute)||(ClosestPeriod.size()==0)){
        return;
    }
    outputScheduleStruct output;
    int repeated,remainMinutesToClose,remainMinutesToOpen;
    for(int i=0;i<ClosestPeriod.size();i++){
        repeated=0;
        for(int j=0;j<timetableOutput.size();j++){
            if(timetableOutput[j].name==schedule[ClosestPeriod[i]].name){
                repeated++;
            }
        }
        if(repeated==0){
            remainMinutesToOpen=60*(schedule[ClosestPeriod[i]].openingTimeHour-timeHour)+schedule[ClosestPeriod[i]].openingTimeMinute-timeMinute;
            if((remainMinutesToOpen>Time_to_reach))
                FindNewTimeWhenThereIsGap(timeHour,timeMinute,schedule[ClosestPeriod[i]]);
            remainMinutesToClose=schedule[ClosestPeriod[i]].closingTimeMinute-timeMinute+60*(schedule[ClosestPeriod[i]].closingTimeHour-timeHour);
            if(remainMinutesToClose>=Min_stay+Time_to_reach){
                int startTimeMinute,startTimeHour,finishTimeHour,finishTimeMinute;
                FindStartTimeToVisit(startTimeMinute,startTimeHour,timeHour,timeMinute,remainMinutesToClose);
                FindFinishTimeToVisit(startTimeMinute,startTimeHour,finishTimeHour,finishTimeMinute,remainMinutesToClose);
                findNewTime(timeHour,timeMinute,remainMinutesToClose);
                MakeNewStructForOnePlace(output,startTimeMinute,startTimeHour,finishTimeHour,finishTimeMinute,schedule[ClosestPeriod[i]].name);
                timetableOutput.push_back(output);
                MakeTimetable(schedule,timetableOutput,timeHour,timeMinute);
                break;
            }
        }
    }    
}

void doProcessOnInput(vector<scheduleStruct>& schedule,vector<outputScheduleStruct>& timetableOutput){
    sortMyVectorOfStruct(schedule);
    int timeHour=7;
    int timeMinute=30;
    MakeTimetable(schedule,timetableOutput,timeHour,timeMinute);
}

void printOutput(vector<outputScheduleStruct>& timetableOutput){
    for(int i=0;i<timetableOutput.size();i++){
        if(i>0)
            cout<<endl;
        cout<<"Location "<<timetableOutput[i].name<<endl;
        if(timetableOutput[i].startTimeHour<10){
            cout<<"Visit from 0"<<timetableOutput[i].startTimeHour<<":";
        }
        else{
            cout<<"Visit from "<<timetableOutput[i].startTimeHour<<":";
        }
        if(timetableOutput[i].startTimeMinute<10){
            cout<<"0"<<timetableOutput[i].startTimeMinute;
        }
        else{
            cout<<timetableOutput[i].startTimeMinute;
        }
        if(timetableOutput[i].finishTimeHour<10){
            cout<<" until 0"<<timetableOutput[i].finishTimeHour<<":";
        }
        else{
            cout<<" until "<<timetableOutput[i].finishTimeHour<<":";
        }
        if(timetableOutput[i].finishTimeMinute<10){
            cout<<"0"<<timetableOutput[i].finishTimeMinute;
        }
        else{
            cout<<timetableOutput[i].finishTimeMinute;
        }
        cout<<"\n"<<"---";
    }
}

int main(int argc, char* argv[]){
    string filename=argv[1];
    vector<scheduleStruct> schedule;
    readInput(schedule,filename);
    vector<outputScheduleStruct> timetableOutput;
    doProcessOnInput(schedule,timetableOutput);
    printOutput(timetableOutput);
}