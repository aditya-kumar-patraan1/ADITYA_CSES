#include<bits/stdc++.h>
using namespace std;

void buildSegmentTree(long long i,long long l,long long r,long long* segmentTree,vector<long long>& a){
    
    if(l==r){
        segmentTree[i] = a[l];
        return;
    }
    long long mid=l+(r-l)/2;
    buildSegmentTree(2*i+1,l,mid,segmentTree,a);
    buildSegmentTree(2*i+2,mid+1,r,segmentTree,a);
    segmentTree[i] = segmentTree[2*i+1]+segmentTree[2*i+2];
}

long long querySum(long long i,long long l,long long r,long long start,long long end,long long* segmentTree){
    
    if(end<l || r<start){
        return 0;
    }
    
    if(start<=l && r<=end){
        return segmentTree[i];
    }
    
    long long mid=l+(r-l)/2;
    return querySum(2*i+1,l,mid,start,end,segmentTree)+querySum(2*i+2,mid+1,r,start,end,segmentTree);
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

    long long *segmentTree = new long long[4 * n]();

    buildSegmentTree(0,0,n-1,segmentTree,a);

    for(long long i=0;i<t;i++){
        long long start=q[i].first;
        long long end=q[i].second;
        cout<<querySum(0,0,n-1,start-1,end-1,segmentTree)<<endl;
    }
    return 0;
}