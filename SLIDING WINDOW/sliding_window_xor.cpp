#include <bits/stdc++.h>
using namespace std;

int main() 
{
    long long n,k;
    long long x,a,b,c;
    cin>>n>>k;
    cin>>x>>a>>b>>c;
    vector<long long> A(n);
    A[0]=x;
    for(int i=1;i<n;i++){
      A[i] = ((A[i-1]*1LL*a)+b)%c;
    }
    long long ans=0LL;
    long long sum = 0LL;
    vector<long long> bits(64,0LL);
    int i=0;
    while(i<min(n,k)){
      sum=sum^A[i++];
    }
    ans=sum;
    int p=0;
    while(i<n){
      sum=sum^A[p++];
      sum=sum^A[i++];
      ans=ans^sum;
    }
    cout<<ans<<endl;
    return 0;
}