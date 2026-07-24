#include<bits/stdc++.h>
using namespace std;

int solve(vector<int>& nums,int n){
    
    vector<int> seq;

    for(int i=0;i<n;i++){
        if(seq.empty() || seq.back()<nums[i]){
            seq.push_back(nums[i]);
        }
        else{
            int idx = lower_bound(begin(seq),end(seq),nums[i]) - begin(seq);
            seq[idx] = nums[i];
        }
    }

    return seq.size();
    
}

int main(){
    int n;
    cin>>n;

    vector<int> a(n,-1);

    for(int i=0;i<n;i++){
        cin>>a[i];
    }

    cout<<solve(a,n);

}