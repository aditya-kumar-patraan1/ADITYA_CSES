#include<bits/stdc++.h>
using namespace std;

void buildSegmentTree(long long i,long long l,long long r,vector<long long>& hotels,long long* segmentTree){
    if(l==r){
        segmentTree[i] = hotels[l];
        return;
    }
    long long mid=l+(r-l)/2;
    buildSegmentTree(2*i+1,l,mid,hotels,segmentTree);
    buildSegmentTree(2*i+2,mid+1,r,hotels,segmentTree);
    segmentTree[i]=max(segmentTree[2*i+1],segmentTree[2*i+2]);
}

long long queryMax(long long i,long long l,long long r,long long capacityNeeded,long long* segmentTree){
    
    if(capacityNeeded>segmentTree[i]){
        return -1;
    }

    if(l==r){  //i have that >= capacity
        segmentTree[i]=segmentTree[i]-capacityNeeded;
        return l;
    }
    long long mid=l+(r-l)/2;
    long long ansIdx=-1;
    ansIdx=queryMax(2*i+1,l,mid,capacityNeeded,segmentTree);    //leftMost dhundho bhai
    if(ansIdx==-1 && segmentTree[2*i+2]>=capacityNeeded){
        ansIdx=queryMax(2*i+2,mid+1,r,capacityNeeded,segmentTree);
    }
    segmentTree[i]=max(segmentTree[2*i+1],segmentTree[2*i+2]);
    return ansIdx;
}

int main(){

    long long m,n;
    cin>>m>>n;
    vector<long long> hotels(m,0);
    vector<long long> customer(n,0);
    for(long long i=0;i<m;i++){
        cin>>hotels[i];
    }
    for(long long i=0;i<n;i++){
        cin>>customer[i];
    }

    long long N=m*4;
    long long* segmentTree = new long long[N];

    buildSegmentTree(0,0,m-1,hotels,segmentTree);
    vector<long long> ans;
    for(long long i=0;i<n;i++){
        long long idx=queryMax(0,0,m-1,customer[i],segmentTree);
        cout<<idx+1<<endl;
    }
    return 0;
}