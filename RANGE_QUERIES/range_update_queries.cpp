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
    segmentTree[i]=segmentTree[2*i+1]+segmentTree[2*i+2];
}

long long querySum(long long i,long long l,long long r,long long start,long long end,long long* segmentTree,long long* lazy){
    
    if(lazy[i]!=0){
        segmentTree[i]+=((r-l+1)*lazy[i]);
        if(l!=r){
            lazy[2*i+1]+=lazy[i];
            lazy[2*i+2]+=lazy[i];
        }
        lazy[i]=0;
    }
    
    if(end<l || r<start){
        return 0;
    }
    if(start<=l && r<=end){
        return segmentTree[i];
    }
    long long mid=l+(r-l)/2;
    return querySum(2*i+1,l,mid,start,end,segmentTree,lazy)+querySum(2*i+2,mid+1,r,start,end,segmentTree,lazy);
}

void lazyPropogate(long long i,long long l,long long r,long long* segmentTree,long long* lazy){
    if(lazy[i]!=0){
        segmentTree[i]+=((r-l+1)*lazy[i]);
        if(l!=r){
            lazy[2*i+1]+=lazy[i];
            lazy[2*i+2]+=lazy[i];
        }
        lazy[i]=0;
    }
}

void queryUpdate(long long i,long long l,long long r,long long start,long long end,long long value,long long* segmentTree,long long* lazy){
    lazyPropogate(i,l,r,segmentTree,lazy);
    if(end<l || r<start){
        return;
    }
    if(start<=l && r<=end){
        lazy[i]+=value;
        lazyPropogate(i,l,r,segmentTree,lazy);
        return;
    }
    long long mid=l+(r-l)/2;
    queryUpdate(2*i+1,l,mid,start,end,value,segmentTree,lazy);
    queryUpdate(2*i+2,mid+1,r,start,end,value,segmentTree,lazy);
    segmentTree[i]=segmentTree[2*i+1]+segmentTree[2*i+2];
}

int main(){
    long long n,t;
    cin>>n>>t;

    vector<long long> a(n,0);

    for(long long i=0;i<n;i++){
        cin>>a[i];
    }

    vector<vector<long long>> q(t,vector<long long>(4,0));

    for(long long i=0;i<t;i++){
        cin>>q[i][0];
        if(q[i][0] == 1){
            cin>>q[i][1]>>q[i][2]>>q[i][3];
        }
        else{
            cin>>q[i][1];
        }
    }

    long long* segmentTree = new long long[4*n];
    long long* lazy = new long long[4*n]();

    build(0,0,n-1,segmentTree,a);

    for(long long i=0;i<t;i++){
        long long type=q[i][0];
        if(type==1){
            long long start=q[i][1]-1;
            long long end=q[i][2]-1;
            long long value=q[i][3];
            queryUpdate(0,0,n-1,start,end,value,segmentTree,lazy);
        }
        else{
            long long start = q[i][1]-1;
            cout<<querySum(0,0,n-1,start,start,segmentTree,lazy)<<endl;
        }
    }

    return 0;
}
