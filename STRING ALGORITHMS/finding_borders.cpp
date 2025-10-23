#include<bits/stdc++.h>
using namespace std;

vector<long long> createLPS(string& s,long long n){
    vector<long long> LPS(n,0LL);
    long long length=0LL;
    LPS[0LL] = length;
    long long j=1LL;

    while(j<n){
        if(s[j] == s[length]){
            length++;
            LPS[j] = length;
            j++;
        }
        else{
            if(length>0){
                length = LPS[length-1];
            }
            else{
                j++;
            }
        }
    }

    return LPS;
}


int main(){
    string s;
    cin>>s;
    long long n=s.length();
    vector<long long> LPS = createLPS(s,n);
    sort(begin(LPS),end(LPS));
    for(long long i=0LL;i<n;i++){
        if(LPS[i] == 0){
            continue;
        }
        cout<<LPS[i]<<' ';
    }
    cout<<endl;
    return 0;
}