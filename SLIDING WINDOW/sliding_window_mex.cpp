#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,k;
    cin>>n>>k;
    int mex=0;
    vector<int> a(n);

    for(int i=0;i<n;i++){
        cin>>a[i];
    }

    vector<int> cnt(n,0);
    vector<int> ans;
    set<int> st;

    for(int i=0;i<=n;i++) st.insert(i);

    auto removee = [&](int ele){
        if(ele>=n){
            return;
        }
        cnt[ele]--;
        if(cnt[ele] == 0){
            st.insert(ele);
        }
        // if(cnt[ele] == 0 && ele<mex) mex=ele;
    };

    auto add = [&](int ele){
        if(ele>=n){
            return;
        }
        if(cnt[ele]  == 0){
            st.erase(ele);
        }
        cnt[ele]++;
        // while(mex<n && cnt[mex]>0) mex++;
    };

    for(int i=0;i<n;i++){
        add(a[i]);
        if(i-k>=0){
            removee(a[i-k]);
        }
        if(i>=k-1){
            ans.push_back(*st.begin());
        }
    }

    for(int i : ans){
        cout<<i<<" ";
    }
    cout<<endl;

    return 0;
}