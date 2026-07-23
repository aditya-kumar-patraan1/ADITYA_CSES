#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> makeAdj(vector<int>& edges,int n){
    
    vector<vector<int>> adj(n);
    
    for(int v=0;v<n-1;v++){
        int u = edges[v];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    return adj;

}

void dfs(int u,int par,vector<vector<int>>& adj,vector<vector<int>>& sparseTable){

    sparseTable[0][u] = par;

    for(int v : adj[u]){
        if(u!=v){
            dfs(v,u,adj,sparseTable);
        }
    }

}

int main(){

    int n,q;
    cin>>n>>q;

    vector<int> nums(n-1);

    for(int i=0;i<n-1;i++){
        cin>>nums[i];
    }

    vector<array<int,2>> queries(q);

    for(int i=0;i<q;i++){
        cin>>queries[i][0]>>queries[i][1];
    }

    vector<vector<int>> adj = makeAdj(nums,n);

    int maxN = 18;

    vector<vector<int>> sparseTable(maxN+1,vector<int>(n,-1));

    // filling for the 0-th parent using dfs()
    dfs(0,-1,adj);

    for(int i=0;i<maxN;i++){
        for(int i=1;i<n;i++){
            sparseTable[i][j] = sparseTable[i-1][sparseTable[i-1][j]];
        }
    }

    helper();



    



    return 0;
}