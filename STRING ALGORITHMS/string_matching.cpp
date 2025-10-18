#include<bits/stdc++.h>
using namespace std;


vector<long long> createLPS(string& target,long long n){
  vector<long long> LPS(n,0);
  LPS[0] = 0;
  long long length = 0LL;
  long long j=1LL;
  while(j<n){
    if(target[j] == target[length]){
      length++;
      LPS[j] = length;
      j++;
    }
    else{
      if(length-1>=0){
        length = LPS[length-1LL];
      }
      else{
        LPS[j] = 0LL;
        j++;
      }
    }
  }
  return LPS;
}

long long countOccurences(string& s,string& target,long long m,long long n,vector<long long>& LPS){
  long long ans = 0;
  
  long long i=0LL,j=0LL;
  
  while(i<m){
    if(s[i] == s[j]){
      i++;
      j++;
    }
    if(j == m){
      ans++;
    }
    if(s[i]!=s[j]){
      if(j-1>=0){
        j = LPS[j-1];
      }
      else{
        i++;
      }
    }
  }
  return ans;
  
}

int main(){
  
  
  string s = "abdjfbejhfguygrrhgggfghhhjgggjhkhjihjggg";
  
  string target = "gg";
  
  
  vector<long long> LPS = createLPS(target,target.length());
  
  return 0;
}
