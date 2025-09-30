#include <bits/stdc++.h>
using namespace std;

int main() 
{
    long long n,k;
    cin>>n>>k;
    vector<long long> A(n);
    for(int i=0;i<n;i++){
        cin>>A[i];
    }
    //first window
    int i=0;
    vector<long long> ans;
    unordered_map<long long,long long> mymap;
    while(i<min(n,k)){
      mymap[A[i++]]++;
    }
    ans.push_back(mymap.size());
    int p=0;
    while(i<n){
      mymap[A[p]]--;
      if(mymap[A[p]] == 0) {
        mymap.erase(A[p]);
      }
      p++;
      mymap[A[i++]]++;
      ans.push_back(mymap.size());
    }
    for(int i : ans){
        cout<<i<<" ";
    }
    cout<<endl;
    return 0;
}