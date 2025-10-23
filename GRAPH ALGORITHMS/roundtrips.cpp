#include <bits/stdc++.h>
using namespace std;

vector<bool> visited;
stack<long long> stk;

bool f(long long n,vector<vector<long long>>& adj,long long u,long long p){
  
  stk.push(u);
  visited[u]=true;
  
  for(long long v : adj[u]){
    if(v == p) continue;
    vector<long long> ans;
    if (visited[v]) {
    stack<long long> temp = stk;
    vector<long long> rev;
    while (!temp.empty()) {
        rev.push_back(temp.top());
        if (temp.top() == v) break;
        temp.pop();
    }
    cout<<rev.size()+1LL<<endl;
    reverse(rev.begin(), rev.end());
    for (auto x : rev) cout << x + 1 << " ";
    cout << v + 1 << endl;
    return true;
}

    if(f(n,adj,v,u)){
      return true;
    }
  }
  stk.pop();
  return false;
}

int main() 
{
    
    long long n,m;
    cin>>n>>m;
    vector<vector<long long>> adj(n);
    
    for(long long i=0LL;i<m;i++){
      long long u,v;
      cin>>u>>v;
      u--;
      v--;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
    visited.resize(n,false);
    for(long long i=0LL;i<n;i++){
      if(visited[i]==false){
        if(f(n,adj,i,-1LL)){
          return 0;
        }
      } 
    }
    cout<<"IMPOSSIBLE"<<endl;
    return 0;
}