#include<bits/stdc++.h>
using namespace std;

int main(){

  long long n,k;
  long long x,a,b,c;
  cin>>n>>k;
  cin>>x>>a>>b>>c;
  vector<long long> A(n);
  A[0]=x;
  for(int i=1;i<n;i++){
    A[i] = ((A[i-1]*1LL*a)+b)%c;
  }  
  long long ans = 0LL;
  deque<int> dq;
  for(int i=0;i<n;i++){
    while(!dq.empty() && dq.front()<=i-k){
      dq.pop_front();
    }
    while(!dq.empty() && A[dq.back()]>=A[i]){
      dq.pop_back();
    }
    dq.push_back(i);
    if(i>=k-1){
      ans=ans^A[dq.front()];
    }
  }
  cout<<ans<<endl;
  return 0;
}