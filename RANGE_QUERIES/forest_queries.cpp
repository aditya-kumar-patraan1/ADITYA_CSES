#include<bits/stdc++.h>
using namespace std;

long long M;

void buildY(long long row,long long startX,long long endX,long long i,long long l,long long r,long long** segmentTree,vector<vector<char>>& grid){
    if(l == r){    //base cell of the matrix
        if(startX==endX){
            segmentTree[row][i]=grid[startX][l]=='*';
        }
        else{
            segmentTree[row][i]=segmentTree[2*row+1][i]+segmentTree[2*row+2][i];
        }
        return;
    }
    long long mid=l+(r-l)/2;
    buildY(row,startX,endX,2*i+1,l,mid,segmentTree,grid);
    buildY(row,startX,endX,2*i+2,mid+1,r,segmentTree,grid);
    segmentTree[row][i]=segmentTree[row][2*i+1]+segmentTree[row][2*i+2];
}

void buildX(long long i,long long l,long long r,long long** segmentTree,vector<vector<char>>& grid){
    if(l==r){   //each row reached
        buildY(i,l,r,0,0,M-1,segmentTree,grid);
        return;
    }
    long long mid=l+(r-l)/2;
    buildX(2*i+1,l,mid,segmentTree,grid);
    buildX(2*i+2,mid+1,r,segmentTree,grid);
    buildY(i,l,r,0,0,M-1,segmentTree,grid);
}

long long querySumY(long long row,long long i,long long l,long long r,long long y1,long long y2,long long** segmentTree){
    if(y2<l || r<y1){
        return 0;
    }
    if(y1<=l && r<=y2){
        return segmentTree[row][i];
    }
    long long mid=l+(r-l)/2;
    return querySumY(row,2*i+1,l,mid,y1,y2,segmentTree)+querySumY(row,2*i+2,mid+1,r,y1,y2,segmentTree);
}

long long querysumX(long long i,long long l,long long r,long long x1,long long y1,long long x2,long long y2,long long** segmentTree){
    if(r<x1 || x2<l){   //out of bound case
        return 0;
    }
    if(l==r){
        return querySumY(i,0,0,M-1,y1,y2,segmentTree);
    }
    if(x1<=l && r<=x2){
        return querySumY(i,0,0,M-1,y1,y2,segmentTree);
    }
    long long mid=l+(r-l)/2;
    return querysumX(2*i+1,l,mid,x1,y1,x2,y2,segmentTree) + querysumX(2*i+2,mid+1,r,x1,y1,x2,y2,segmentTree);
}

int main(){
     std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    long long m,t;
    cin>>m>>t;
    M=m;
    vector<vector<char>> grid(M,vector<char>(M,'.'));
    for(long long i=0;i<M;i++){
        for(long long j=0;j<M;j++){
            cin>>grid[i][j];
        }
    }
    vector<vector<long long>> q(t,vector<long long>(4,0));
    for(long long i=0;i<t;i++){
        cin>>q[i][0]>>q[i][1]>>q[i][2]>>q[i][3];
    }

    long long sz=4*M;

    long long** segmentTree = new long long*[sz];

    for(long long i=0;i<sz;i++){
        segmentTree[i]=new long long[sz]();
    }

    buildX(0,0,M-1,segmentTree,grid);


    for(long long i=0;i<t;i++){
        long long x1=q[i][0]-1;
        long long y1=q[i][1]-1;
        long long x2=q[i][2]-1;
        long long y2=q[i][3]-1;
        cout<<querysumX(0,0,M-1,x1,y1,x2,y2,segmentTree)<<endl;
    }

    for(int i=0; i<sz; i++){
        delete[] segmentTree[i];
    }
    delete[] segmentTree;

    return 0;

}