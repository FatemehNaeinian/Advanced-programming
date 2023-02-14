#include <iostream>
#include <vector>
#include <string>
using namespace std;

void invert(vector<int>& S,int i){
    if(i==0){
         return ;
    }
    if(S[i-1]==1){
        S[i-1]=0;
    }
    else{
        S[i-1]=1;
    }
    invert(S,i-1);
     return ;
}
void reverse(vector<int>sInvert,vector<int>&sReverse,int i){
    if(i==0){
        return ;
    }
    else{
        sReverse.push_back(sInvert[i-1]);
        reverse(sInvert,sReverse,i-1);
    }
    return ;
}

void MakeSn(vector<int>&Sn,int n){
    if(n==1)
        Sn.push_back(0);
    else{
        MakeSn(Sn,n-1);
        vector<int> one(1,1);
        vector<int> Si;
        for(int e=0;e<Sn.size();e++){
            Si.push_back(Sn[e]);
        }
        invert(Si,Si.size());
        vector<int> sReverse;
        reverse(Si,sReverse,Si.size());
        Sn.insert(Sn.end(),one.begin(),one.end());
        Sn.insert(Sn.end(),sReverse.begin(),sReverse.end());
        return;
    }
}

int main(){
    int n,k;
    cin>>n;
    cin>>k;
    vector<int> Sn;
    MakeSn(Sn,n);
    cout<< Sn[k-1]<<endl;
}