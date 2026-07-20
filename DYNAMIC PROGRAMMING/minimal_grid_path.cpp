#include <bits/stdc++.h>
using namespace std;

using T = tuple<char, int, int>;

bool boundaryChecking(int i, int j, int n)
{
    return i >= 0 && j >= 0 && i < n && j < n;
}

int main()
{
    int n;
    cin >> n;

    vector<string> grid(n);

    for (int i = 0; i < n; i++)
    {
        string s = "";
        cin >> s;
        grid[i] = s;
    }

    queue<T> q;
    q.push({grid[0][0], 0, 0});

    // cout<<"n is : "<<n<<endl;

    string ans = "";

    vector<vector<bool>> st(n,vector<bool>(n,false));

    while (!q.empty())
    {

        int length = q.size();

        vector<pair<int, int>> temp[26];
        bool f = false;
        while (length)
        {
            T curr = q.front();
            char ch = get<0>(curr);
            int i = get<1>(curr);
            int j = get<2>(curr);

            q.pop();
            if(!f){
                f=true;
                ans += ch;
            }

            if (i == n - 1 && j == n - 1)
            {
                cout << ans << endl;
                return 0;
            }

            if (boundaryChecking(i, j + 1, n) && !st[i][j+1])
            {
                // cout<<grid[i][j+1]<<endl;
                temp[grid[i][j + 1] - 'A'].push_back(make_pair(i, j + 1));
                st[i][j+1] = true;
            }

            if (boundaryChecking(i + 1, j, n) && !st[i + 1][j])
            {
                // cout<<"case 2"<<endl;
                temp[grid[i + 1][j] - 'A'].push_back(make_pair(i + 1, j));
                st[i+1][j] = true;
            }
            length -= 1;
        }

        int idx = -1;

        for (int i = 0; i < 26; i++)
        {
            if (temp[i].size() > 0)
            {
                idx = i;
                break;
            }
        }

        // cout<<"idx is : "<<idx<<endl;

        if (idx != -1)
        {
            char ch = idx + 'A';
            for (pair<int, int> &p : temp[idx])
            {
                q.push({ch, p.first, p.second});
            }
        }
    }

    return 0;

}