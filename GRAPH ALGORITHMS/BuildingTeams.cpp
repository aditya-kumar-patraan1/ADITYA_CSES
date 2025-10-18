#include<bits/stdc++.h>
using namespace std;

typedef long long ll;


bool f(vector<vector<ll>>& adj,ll u,vector<ll>& colors,ll color){
  
   colors[u]= color;   //filling the current node with color
  
  for(ll v : adj[u]){
    if(color==colors[v]){
      return false;
    }
    if(colors[v]!=-1LL) continue;
    if(!f(adj,v,colors,1LL-color)){
        return false;
    }
  }
  return true;
}

int main(){
  
  ll n,m;
  cin>>n>>m;
  
  vector<vector<ll>> adj(n);
  
  for(ll i=0LL;i<m;i++){
    ll u,v;
    cin>>u>>v;
    u--;
    v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  
  vector<ll> colors(n,-1LL);
  
  for(ll i=0LL;i<n;i++){
    if(colors[i]==-1LL){
      // cout<<"for i : "<<i<<endl;
      if(!f(adj,i,colors,0LL)){
        cout<<"IMPOSSIBLE"<<endl;
        return 0;
      }
    }
  }
  
  for(ll i : colors){
    cout<<i+1LL<<" ";
  }
  cout<<endl;
  
  return 0;
}