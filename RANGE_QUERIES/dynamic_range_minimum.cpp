#include<bits/stdc++.h>
using namespace std;

void build(int i,int l,int r,int* segmentTree,vector<int>& a){
    if(l==r){
        segmentTree[i] = a[l];
        return;
    }
    int mid=l+(r-l)/2;
    build(2*i+1,l,mid,segmentTree,a);
    build(2*i+2,mid+1,r,segmentTree,a);
    segmentTree[i] = min(segmentTree[2*i+1],segmentTree[2*i+2]);
}

void updateQuery(int i,int l,int r,int idx,int val,int* segmentTree){
    if(l==r){
        segmentTree[i]=val;
        return;
    }
    int mid=l+(r-l)/2;
    if(idx<=mid){
        updateQuery(2*i+1,l,mid,idx,val,segmentTree);
    }
    else{
        updateQuery(2*i+2,mid+1,r,idx,val,segmentTree);
    }
    segmentTree[i]=min(segmentTree[2*i+1],segmentTree[2*i+2]);
}

int queryMin(int i,int l,int r,int start,int end,int* segmentTree){
    if(end<l || r<start){
        return INT_MAX;
    }
    if(start<=l && r<=end){
        return segmentTree[i];
    }
    int mid=l+(r-l)/2;
    return min(queryMin(2*i+1,l,mid,start,end,segmentTree),queryMin(2*i+2,mid+1,r,start,end,segmentTree));
}

int main(){
    int n,t;
    cin>>n>>t;

    vector<int> a(n,0);

    for(int i=0;i<n;i++){
        cin>>a[i];
    }

    vector<vector<int>> q(t,vector<int>(3,0));

    for(int i=0;i<t;i++){
        cin>>q[i][0]>>q[i][1]>>q[i][2];
    }

    int* segmentTree = new int[4*n];
    
    build(0,0,n-1,segmentTree,a);

    for(int i=0;i<t;i++){
        int type=q[i][0];
        if(type==1){
            int idx=q[i][1]-1;
            int val=q[i][2];
            updateQuery(0,0,n-1,idx,val,segmentTree);
        }
        else{
            int start = q[i][1]-1;
            int end = q[i][2]-1;
            cout<<queryMin(0,0,n-1,start,end,segmentTree)<<endl;
        }
    }

    return 0;
}