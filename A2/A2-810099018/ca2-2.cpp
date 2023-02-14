#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

vector<string> Periority(int positionStr,vector<string>& codeStr){
    vector<string> decode;
    if(positionStr>=codeStr.size()-1)
        return decode;
    int posOpen=codeStr.size()-1;
    int posClose=codeStr.size()-1;
    for(int y=positionStr+1;y<codeStr.size();y++){
        if(codeStr[y]=="["){
            posOpen=y;
            break;
        }
    }

    for(int t=positionStr;t<codeStr.size();t++){
        if(codeStr[t]=="]"){
            posClose=t;
            break;
        }
    }

    if(posOpen>=posClose){
        string numberDetector1=codeStr[positionStr-1];
        int k1=stoi(numberDetector1);
        for(int r=0;r<k1;r++){
            for(int e=0;e<posClose-positionStr-1;e++){
                decode.push_back(codeStr[positionStr+e+1]);
            }
        }
        if(posOpen>posClose){
            vector<string> linearDecode;
            linearDecode=Periority(posOpen,codeStr);
            for(int q2=0;q2<linearDecode.size();q2++){
                decode.push_back(linearDecode[q2]);
            }
        }
        return decode;
    }

    else{
        vector<string> innerDecode;
        innerDecode=Periority(posOpen,codeStr);
        string numberDetector2=codeStr[positionStr-1];
        int k2=stoi(numberDetector2);
        for(int o=0;o<k2;o++){
            for(int p=0;p<posOpen-positionStr-2;p++){
                decode.push_back(codeStr[positionStr+p+1]);
            }
            for(int q=0;q<innerDecode.size();q++){
                decode.push_back(innerDecode[q]);
            }
        }
        return decode;

    }
}

void Decoding(vector<string>& S,vector<string>& codeStr){
    int positionStr=0;
    vector<string> code;
    string NumberDetector=codeStr[positionStr];
    char* IsNumber;
    strtol(NumberDetector.c_str(), &IsNumber, 10);
    if(*IsNumber== '\0'){
        if(codeStr[positionStr+1]=="["){
            code=Periority(positionStr+1,codeStr);
            S.insert(S.end(),code.begin(),code.end());
            return;
        }
    }
    else{
        int posOpen=positionStr+2;
        for(int y=0;y<codeStr.size();y++){
            if(codeStr[y]=="["){
                posOpen=y;
                break;
            }
        }
        for(int w=0;w<posOpen-1;w++)
            S.push_back(codeStr[w]);
        code=Periority(posOpen,codeStr);
        S.insert(S.end(),code.begin(),code.end());
        return;
    }

}

int main(){
    string code;
    getline(cin,code);
    vector<string> S;
    vector<char> codeChar(code.begin(),code.end());
    vector<string> codeStr(codeChar.size());
    for(int i=0;i<codeChar.size();i++){
        codeStr[i]=codeChar[i];
    }
    Decoding(S,codeStr);

    for(string h:S)
        cout<<h;
    cout<<endl;
}