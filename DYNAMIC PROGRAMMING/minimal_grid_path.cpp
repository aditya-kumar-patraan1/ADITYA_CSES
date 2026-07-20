#include<bits/stdc++.h>
using namespace std;


int main(){
    int m,n;
    cin>>m>>n;

    vector<string> grid(m);

    for(int i=0;i<n;i++){
        string s = "";
        cin>>s;
        grid[i] = s;
    }

    vector<vector<int>> dp(m,vector<int>(n));

}