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
            return parent[node] = ultimateParent(parent[node]);
        }

        void Union(long long u,long long v){
            long long ulp_u=ultimateParent(u);
            long long ulp_v=ultimateParent(v);
            if(ulp_u==ulp_v){
                return;
            }
            else if(rank[ulp_u]<rank[ulp_v]){
                parent[ulp_u]=ulp_v;
            }
            else if(rank[ulp_v]<rank[ulp_u]){
                parent[ulp_v]=ulp_u;
            }
            else{
                parent[ulp_u]=ulp_v;
                rank[ulp_v]++;
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
        u--;
        v--;
        adj.push_back(make_pair(u,v));
    }
  
    DSU myNetwork = DSU(n);

    for(int i=0;i<m;i++){
        long long u=adj[i].first;
        long long v=adj[i].second;
        myNetwork.Union(u,v);
    }
    // cout<<"hii"<<endl;
    

    vector<long long> leader;

    for(long long i=0;i<n;i++){
        if(myNetwork.parent[i]==i){
            leader.push_back(i);
        }
    }

    cout<<leader.size()-1<<endl;

    for(long long i=0;i<(long long)(leader.size())-1LL;i++){
        cout<<leader[i]+1<<" "<<leader[i+1]+1<<endl;
    }

    return 0;
}