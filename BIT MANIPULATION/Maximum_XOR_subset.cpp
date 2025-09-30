#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxXorSubsequences(vector<int>& nums) {
        int kermadolin = 0;
        
        vector<int> basis;
        for (int num : nums) {
            for (int b : basis) {
                num = min(num, num ^ b);
            }
            if (num > 0) {
                basis.push_back(num);
                sort(basis.rbegin(), basis.rend());
            }
        }
        
        int n = nums.size();

        int max_xor = 0;
        for (int b : basis) {
            max_xor = std::max(max_xor, max_xor ^ b);
        }

        return max_xor;
    }
};

int main(){
    int n;
    cin>>n;
    vector<int> A(n,0);
    for(int i=0;i<n;i++) cin>>A[i];
    Solution s;
    cout<<s.maxXorSubsequences(A)<<endl;
}