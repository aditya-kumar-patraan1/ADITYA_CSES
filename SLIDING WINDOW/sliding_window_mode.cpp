#include <bits/stdc++.h>
using namespace std;

int main() 
{
    long long n,k;
    cin>>n>>k;
    vector<long long> A(n);
    for(int i=0;i<n;i++) cin>>A[i];

    vector<long long> ans;
    unordered_map<long long,long long> freq;
    multiset<pair<long long,long long>> ms; // {frequency, value}

    // First window
    for(int i=0;i<k;i++){
        if(freq[A[i]] > 0)
            ms.erase(ms.find({freq[A[i]], A[i]}));
        freq[A[i]]++;
        ms.insert({freq[A[i]], A[i]});
    }
    long long max_freq=prev(ms.end())->first;
    auto it = ms.lower_bound({max_freq, LLONG_MIN});
    ans.push_back(it->second);

    // Sliding window
    for(int i=k, p=0; i<n; i++, p++){
        // Remove outgoing
        ms.erase(ms.find({freq[A[p]], A[p]}));
        freq[A[p]]--;
        if(freq[A[p]] > 0)
            ms.insert({freq[A[p]], A[p]});
        else
            freq.erase(A[p]);

        // Add incoming
        if(freq[A[i]] > 0)
            ms.erase(ms.find({freq[A[i]], A[i]}));
        freq[A[i]]++;
        ms.insert({freq[A[i]], A[i]});
        
        long long max_frq=prev(ms.end())->first;
        auto it = ms.lower_bound({max_frq, LLONG_MIN});
        ans.push_back(it->second);
    }

    for(long long x : ans) cout << x << " ";
    cout << endl;
}
