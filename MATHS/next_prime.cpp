#include<bits/stdc++.h>
using namespace std;

bool isPrime(int num){
    if(num%2==0 || num==1){
        return false;
    }
    if(num==2){
        return true;
    }
    for(int i=3;i<num;i+=2){
        if(num%i==0){
            return false;
        }
    }
    return true;
}

int main(){

    int n;
    cin>>n;

    for(int i=n+1;i<=n+600;i++){
        if(isPrime(i)){
            cout<<i<<endl;
            break;
        }
    }

    return 0;
}