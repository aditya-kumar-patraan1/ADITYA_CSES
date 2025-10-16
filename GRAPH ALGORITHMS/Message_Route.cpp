#include<bits/stdc++.h>
using namespace std;

long long dijkstra(vector<long long>& parent,vector<vector<long long>>& adj,long long n,long long src,long long dest){
    priority_queue<pair<long long,long long>,vector<pair<long long,long long>>,greater<pair<long long,long long>>> pq;
    vector<long long> distance(n,INT_MAX);
    distance[0]=0;
    parent[0]=-1LL;
    pq.push(make_pair(distance[0],0));
    
    while(!pq.empty()){
        long long dist=pq.top().first;
        long long u=pq.top().second;
        pq.pop();
        if(u == dest){
            return dest;
        }
        if(dist>distance[u]){
            continue;
        }
        for(long long v : adj[u]){
            if(dist + 1 < distance[v]){
                distance[v] = dist + 1;
                parent[v]=u;
                pq.push(make_pair(distance[v],v));
            }
        }
    }
    
    return distance[dest];
}

int main(){
    
    long long n,m;
    cin>>n>>m;
    vector<pair<long long,long long>> edges;
    
    for(int i=0;i<m;i++){
        long long u,v;
        cin>>u>>v;
        u--;
        v--;
        edges.push_back(make_pair(u,v));
    }

    vector<vector<long long>> adj(n);
    
    for(int i=0;i<n;i++){
        long long u=edges[i].first;
        long long v=edges[i].second;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    vector<long long> parent(n,-1LL);
    long long data=dijkstra(parent,adj,n,0,n-1);
    
    if(data==INT_MAX){
        cout<<"NOT POSSIBLE"<<endl;
    }
    else{
        cout<<data<<endl;
        long long node=n-1;
        while(node!=-1LL){
            cout<<node+1<<" ";
            node=parent[node];
        }
        cout<<endl;
    }
    return 0;
}