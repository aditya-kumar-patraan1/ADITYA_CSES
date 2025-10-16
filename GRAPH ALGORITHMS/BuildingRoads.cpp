#include<bits/stdc++.h>
using namespace std;

class DSU{
    public:
        vector<long long> parent;
        vector<long long> rank;

        DSU(long long n){
            parent.resize(n);
            rank.resize(n,0);
            for(long long i=0;i<n;i++){
                parent[i] = i;
            }
        }

        long long ultimateParent(long long node){
            if(node == parent[node]){
                return node;
            }
            parent[node] = ultimateParent(parent[node]);
        }

        void Union(long long u,long long v){
            long long rank_u=ultimateParent(u);
            long long rank_v=ultimateParent(v);
            if(rank_u==rank_v){
                return;
            }
            else if(rank[rank_u]<rank[rank_v]){
                parent[rank_u]=rank_v;
                rank[rank_v]++;
            }
            else if(rank[rank_v]<rank[rank_u]){
                parent[rank_u]=rank_u;
                rank[rank_u]++;
            }
            else{
                parent[rank_u]=rank_v;
                rank[rank_v]++;
            }
        }        
};

int main(){

    long long n,m;
    cin>>n>>m;
    vector<pair<long long,long long>> adj;

    for(int i=0;i<m;i++){
        long long u,v;
        cin>>u>>v;
        adj.push_back(make_pair(u,v));
    }

    DSU myNetwork = DSU(n);

    for(int i=0;i<m;i++){
        long long u=adj[i].first;
        long long v=adj[i].second;
        myNetwork.Union(u,v);
    }

    return 0;
}