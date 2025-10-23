#include <bits/stdc++.h>
using namespace std;

vector<long long> createLPS(string& pat){
  long long n=pat.length();
  
  
  vector<long long> LPS(n,0);
  long long length = 0;
  LPS[0] = length;
  long long j=1LL;
  
  while(j<n){
    if(pat[j] == pat[length]){
      length++;
      LPS[j] = length;
      j++;
    }
    else{
      if(length>0){
        length=LPS[length-1];
      }
      else{
        LPS[j] = 0LL;
        j++;
      }
    }
  }
  return LPS;
  
}


long long solve(string& s,string& pat,vector<long long>& LPS){
  long long ans=0LL;
  
  long long i=0LL,j=0LL;
  long long m=s.length(),n=pat.length();
  
  while(i<m){
    if(s[i] == pat[j]){
      i++;
      j++;
    }
    if(j == n){
    // cout<<"hi"<<endl;
      ans++;
      j=LPS[j-1];
    }
    if(s[i]!=pat[j]){
      if(j>0){
        j=LPS[j-1];
      }
      else{
        i++;
      }
    }
  }
  return ans;
}

int main() 
{
    string s,pat;
    cin>>s;
    cin>>pat;
    
    vector<long long> LPS = createLPS(pat);
    cout<<solve(s,pat,LPS)<<endl;
    
    return 0;
}