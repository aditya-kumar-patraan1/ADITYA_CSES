#include<bits/stdc++.h>
using namespace std;


int main(){
    int n;
    cin>>n;

    vector<int> aa;
    int t=n;
    while(t>0){
        int num;
        cin>>num;
        aa.push_back(num);
        t-=1;
    }

    unordered_map<int,int> freq;
    
    for(int i=0;i<n;i++){
        freq[aa[i]]++;
    }

    int maxi = *max_element(begin(aa),end(aa));

    for(int gcd=maxi;gcd>=1;gcd--){
        int c = 0;
        bool f = false;
        // cout<<"gcd : "<<gcd<<endl;
        for(int j=gcd;j<=maxi;j+=gcd){
            c+=freq[j];
            // cout<<j<<' ';
            if(c>=2){
                cout<<gcd<<endl;
                f = true;
                break;
            }
        }
        if(f) break;
        // cout<<endl;
        // cout<<"-----"<<endl;
    }

    return 0;
}