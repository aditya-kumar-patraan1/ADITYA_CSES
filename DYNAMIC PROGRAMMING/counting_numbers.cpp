#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll dp[20][10][2][2];

// pos,isBounded,isStarted
ll solve(int pos, int prev, bool isBounded, bool isStarted, string &s, int n)
{

    if (pos == n)
    {
        return 1;
    }

    if (isBounded==false && dp[pos][prev][isBounded][isStarted] != -1)
    {
        return dp[pos][prev][isBounded][isStarted];
    }

    int maxLimit = 9;

    if (isBounded == true)
    {
        maxLimit = s[pos] - '0';
    }

    ll ans = 0LL;

    for (int i = 0; i <= maxLimit; i++)
    {

        if (isStarted == true)
        {
            if (prev != i)
            {
                ans += solve(pos + 1, i, isBounded && (i == (s[pos]-'0')), true, s, n);
            }
        }
        else
        {
            if (i == 0)
            {
                ans += solve(pos + 1, i, isBounded && (i == (s[pos]-'0')), false, s, n);
            }
            else
            {
                ans += solve(pos + 1, i, isBounded && (i == (s[pos]-'0')), true, s, n);
            }
        }
    }

    if (isBounded == false)
    {
        dp[pos][prev][isBounded][isStarted] = ans;
    }

    return ans;
}

ll compute(ll num)
{
    // cout<<num<<endl;
    string s = to_string(num);
    memset(dp, -1, sizeof(dp));
    // cout<<dp[7][5][1][1]<<endl;
    return solve(0, -1, true, false, s, s.length());
}

int main()
{
    ll a, b;
    cin >> a >> b;

    ll deduct = 0;
    if (a > 0)
    {
        deduct = compute(a - 1);
    }

    cout << compute(b) - deduct << endl;
}