#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int dir[4][3]={{0,1},{1,0},{-1,0},{0,-1}};
ll M,N;

void dfs(vector<vector<char>>& grid,ll i,ll j,vector<vector<bool>>& visited){
    visited[i][j]=true;
    for(auto t : dir){
        ll i_=i+t[0];
        ll j_=j+t[1];
        if(i_>=0 && j_>=0 && i_<M && j_<N && visited[i_][j_]==false && grid[i_][j_]!='#'){
            dfs(grid,i_,j_,visited);
        }
    }
}

int main(){
    ll m,n;
    cin>>m>>n;
    M=m,N=n;
    vector<vector<char>> grid(m,vector<char>(n,-1LL));

    for(ll i=0LL;i<m;i++){
        for(ll j=0LL;j<n;j++){
            cin>>grid[i][j];
        }
    }

    ll count=0LL;
    vector<vector<bool>> visited(m,vector<bool>(n,false));

    for(ll i=0LL;i<m;i++){
        for(ll j=0LL;j<n;j++){
            if(visited[i][j]==false && grid[i][j]=='.'){
                dfs(grid,i,j,visited);
                count++;
            }
        }
    }
    cout<<count<<endl;
    return 0;

}