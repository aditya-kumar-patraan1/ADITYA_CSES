#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n, k, x, a, b, c;
    cin >> n >> k >> x >> a >> b >> c;

    vector<long long> A(n);
    A[0] = x;
    for(long long i = 1; i < n; i++) {
        A[i] = (A[i-1]*a + b) % c;
    }

    int bits[64] = {0};
    long long ans = 0;
    long long i = 0;

    // first window
    for(; i < k; i++) {
        long long val = A[i];
        for(int b = 0; b < 64; b++) if(val & (1LL << b)) bits[b]++;
    }

    auto getVal = [&]() {
        long long v = 0;
        for(int b = 0; b < 64; b++) if(bits[b] > 0) v |= (1LL << b);
        return v;
    };

    ans = getVal();
    long long p = 0;

    while(i < n) {
        // reduce A[p]
        long long val = A[p++];
        for(int b = 0; b < 64; b++) if(val & (1LL << b)) bits[b]--;

        // add A[i]
        val = A[i++];
        for(int b = 0; b < 64; b++) if(val & (1LL << b)) bits[b]++;

        ans ^= getVal();
    }

    cout << ans << endl;
}
