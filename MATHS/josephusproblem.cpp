#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

void ss(){
    ll n,k;
    cin>>n>>k;
    if(n%2==1){
        ll evens = n/2LL;
        ll odds = n/2LL + 1LL;

        if(k<=evens){
            cout<<(k*2LL)<<endl;
        }
        else{
            ll rem = k - evens;
            cout<<rem<<endl;
            cout<<(2LL*(rem-1LL))+1LL<<endl;
        }
    }
    else{
        ll evens = n/2LL;
        ll odds = n/2LL;
        if(n==k){
            cout<<1<<endl;
            return;
        }
        if(k<=evens){
            cout<<k*2LL<<endl;
        }
        else{
            ll rem = k - evens;
            cout<<(2LL*rem)+1LL<<endl;
        }
    }
}

int main(){
    ll t;
    cin>>t;
    while(t--){
        ss();
    }
}


