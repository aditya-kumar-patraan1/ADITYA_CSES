#include <bits/stdc++.h>
using namespace std;

int main()
{

    int m, k;
    cin >> m >> k;

    vector<string> grid(m);
    set<char> t;

    for (int i = 0; i < m; i++)
    {
        string s;
        cin >> s;
        grid[i] = s;
        for (char ch : s)
            t.insert(ch);
    }

    // sort(begin(t), end(t));
    // t.erase(unique(begin(t), end(t)), end(t));
    for (char ch : t)
    {
        // cout<<ch<<endl;
        vector<long long> dp(m);
        long long ans = 0;
        for (int j = 0; j < m; j++)
        {
            if (grid[0][j] == ch)
            {
                dp[j] = 1;
                ans++;
            }
        }

        // for (int i = 0; i < m; i++)
        // {
        //     cout << dp[i] << ' ';
        // }
        // cout << endl;

        
        for (int i = 1; i < m; i++)
        {
            vector<long long> temp(m, 0);
            for (int j = 0; j < m; j++)
            {
                if (j == 0)
                {
                    if (grid[i][j] == ch)
                    {
                        ans++;
                        temp[j] = 1;
                    }
                }
                else
                {

                    if (grid[i][j] == ch)
                    {
                        long long mini = dp[j]; // {i-1,j}
                        if (j - 1 >= 0)
                        {
                            mini = min(mini,dp[j - 1]);              // {i-1,j-1}
                            mini = min(mini, temp[j - 1]); // {i,j-1}
                        }
                        mini = (mini == LLONG_MAX ? 0 : mini);
                        temp[j] = mini + 1;
                        ans += temp[j];
                    }
                }
            }
            dp = temp;
        }
        cout << ans << endl;
    }
    return 0;
}
