#include<bits/stdc++.h>
using namespace std;


// bulding min segment Tree
void build(long long i,long long l,long long r,long long* segmentTree,vector<long long>& a){
    if(l == r){
        segmentTree[i] = a[l];
        return;
    }
    long long mid = l + (r-l)/2;

    build(2*i+1,l,mid,segmentTree,a);
    build(2*i+2,mid+1,r,segmentTree,a);
    segmentTree[i]=min(segmentTree[2*i+1],segmentTree[2*i+2]);
}

//handling queries with the help of segment Tree
long long minQuery(long long i,long long l,long long r,long long start,long long end,long long* segmentTree){
    if(end<l || r<start){
        return LLONG_MAX;
    }
    if(start<=l && r<=end){
        return segmentTree[i];
    }
    long long mid = l + (r-l)/2;
    return min(minQuery(2*i+1,l,mid,start,end,segmentTree),minQuery(2*i+2,mid+1,r,start,end,segmentTree));
}

int main(){

    long long n,t;
    cin>>n>>t;
    
    vector<long long> a(n);

    for(long long i=0;i<n;i++){
        cin>>a[i];
    }

    vector<pair<long long,long long>> q(t);

    long long k=0;

    while(k<t){
        cin>>q[k].first>>q[k].second;
        k++;
    }
    
    long long* segmentTree = new long long[4 * n];
    
    build(0,0,n-1,segmentTree,a);

    for(long long i=0;i<t;i++){
        long long start = q[i].first - 1;
        long long end = q[i].second - 1;
        cout<<minQuery(0,0,n-1,start,end,segmentTree)<<endl;
    }

    return 0;

}