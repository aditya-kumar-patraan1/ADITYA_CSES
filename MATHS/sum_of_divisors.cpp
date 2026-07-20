#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 1000000007;

int main()
{

    ll n;
    cin >> n;

    int ans = 0LL;

    for (long long d = 1; d <= n; d++)
        ans += d * (n / d);

    cout << ans << endl;
}