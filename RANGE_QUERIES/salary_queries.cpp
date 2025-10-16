#include<bits/stdc++.h>
using namespace std;

void queryUpdate(long long i,long long l,long long r,long long idx,long long val,long long* segmentTree){
    if(l==r){
        segmentTree[i]+=val;
        return; 
    }
    long long mid=l+(r-l)/2;
    if(idx<=mid){
        // left jao
        queryUpdate(2*i+1,l,mid,idx,val,segmentTree);
    }
    else{
        //right jao
        queryUpdate(2*i+2,mid+1,r,idx,val,segmentTree);
    }
    segmentTree[i]=segmentTree[2*i+1]+segmentTree[2*i+2];
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
    vector<long long> a(n,-1);
    for(long long i=0;i<n;i++){
        cin>>a[i];
    }

    

    //!--->1  queryUpdate()
    //?--->2  count()
    //polong long compression technqiue 
    vector<long long> comp;

    vector<vector<long long>> q(t,vector<long long>(3,-1));
    for(long long i=0;i<t;i++){
        char type;
        cin>>type;
        if(type=='?'){
            //counting task
            q[i][0]=2;
        }
        else{
            //queryUpdate()
            q[i][0]=1;
        }
        cin>>q[i][1]>>q[i][2];
        if(q[i][0]==1){
            comp.push_back(q[i][2]);
        }
    }


    for(long long i=0;i<n;i++){
        comp.push_back(a[i]);
    }

    sort(begin(comp),end(comp));
    comp.erase(unique(begin(comp),end(comp)),end(comp));

    auto getId = [&](long long ele){
        return lower_bound(begin(comp),end(comp),ele)-begin(comp);
    };

    for(long long i=0;i<n;i++){
        a[i]=getId(a[i]);
    }

    long long N=comp.size();

    long long* segmentTree = new long long[4*N];

    for(long long i=0;i<n;i++){
      queryUpdate(0,0,N-1,a[i],1,segmentTree);
    }
    
    vector<long long> result;

    for(long long i=0;i<t;i++){
        long long type=q[i][0];
        if(type==1){
            long long pos=q[i][1]-1;
            long long newValue=getId(q[i][2]);
            queryUpdate(0,0,N-1,a[pos],-1,segmentTree);
            a[pos]=newValue;
            queryUpdate(0,0,N-1,a[pos],1,segmentTree);
        }
        else{
            long long startSalary=getId(q[i][1]);
            long long endSalary=getId(q[i][2]);
            long long answer=querySum(0,0,N-1,startSalary,endSalary,segmentTree);   //blackbox
            result.push_back(answer);
        }
    }

    for(long long i : result){
        cout<<i<<endl;
    }

    return 0;

}

