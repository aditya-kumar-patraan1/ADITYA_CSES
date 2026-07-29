#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int main()
{

    int n;
    cin >> n;

    string s;
    cin >> s;

    int m = s.length();

    if (m >= n)
    {
        if (n == m)
            cout << 1 << endl;
        else
            cout << 0 << endl;
        return 0;
    }

    int rem = n - m;
    // cout<<rem<<endl;
    int ans = 1;

    for (int i = 1; i <= rem; i++)
    {
        ans = (ans % MOD * 1LL * 26) % MOD;
    }

    ans = (ans % MOD * 1LL * (rem + 1) % MOD) % MOD;
    cout<<ans<<endl;
    return 0;
}
