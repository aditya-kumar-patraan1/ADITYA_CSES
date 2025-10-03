#include<bits/stdc++.h>
using namespace std;

void build(long long i,long long l,long long r,long long* segmentTree,vector<long long>& a){
    if(l==r){
        segmentTree[i] = a[l];
        return;
    }
    long long mid=l+(r-l)/2;
    build(2*i+1,l,mid,segmentTree,a);
    build(2*i+2,mid+1,r,segmentTree,a);
    segmentTree[i]=segmentTree[2*i+1]^segmentTree[2*i+2];
}

long long queryXor(long long i,long long l,long long r,long long start,long long end,long long* segmentTree){
    if(end<l || r<start){
        return 0;
    }
    if(start<=l && r<=end){
        return segmentTree[i];
    }
    long long mid=l+(r-l)/2;
    return queryXor(2*i+1,l,mid,start,end,segmentTree)^queryXor(2*i+2,mid+1,r,start,end,segmentTree);
}

int main(){

    long long n,t;
    cin>>n>>t;
    vector<long long> a(n,0);
    for(long long i=0;i<n;i++){
        cin>>a[i];
    }
    vector<pair<long long,long long>> q(t);

    for(long long i=0;i<t;i++){
        cin>>q[i].first>>q[i].second;
    }

    long long* segmentTree = new long long[4*n];

    build(0,0,n-1,segmentTree,a);

    for(long long i=0;i<t;i++){
        long long start = q[i].first-1;
        long long end = q[i].second-1;
        cout<<queryXor(0,0,n-1,start,end,segmentTree)<<endl;
    }
    return 0;

}