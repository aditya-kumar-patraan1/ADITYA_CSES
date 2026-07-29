#include <bits/stdc++.h>
using namespace std;

int main()
{

    string s;
    cin >> s;

    int n = s.length();

    string modifiedS = "#";

    for (int i = 0; i < n; i++)
    {
        modifiedS += s[i];
        modifiedS += '#';
    }

    int newSize = n * 2 + 1;
    vector<int> ans(n, 1);

    int center = 0, right = 0;

    vector<int> palin(newSize, 0);

    // for(char ch : modifiedS) cout<<ch;
    // cout<<endl;

    for (int i = 0; i < newSize; i++)
    {
        int mirror = 2 * center - i;

        // cout<<"i is : "<<i<<endl;
        
        if (right > i)
        {
            palin[i] = min(palin[mirror], right - i);
        }
        int start = (i - palin[i]) / 2;
        int end = (i + palin[i]) / 2 - 1;

        if (start >= 0 && end < n && start<=end && start<n && end>=0)
        {
            ans[end] = max(ans[end], end - start + 1);
            // cout<<"start : "<<start<<endl;
            // cout<<"end : "<<end<<endl;
            // cout<<ans[end]<<endl;
        }

        int a = i + (palin[i] + 1);
        int b = i - (palin[i] + 1);

        while (b >= 0 && a < newSize && modifiedS[b] == modifiedS[a])
        {

            a++;
            b--;
            palin[i]++;
            start = (i - palin[i]) / 2;
            end = (i + palin[i]) / 2 - 1;

            if (start >= 0 && end < n && start<=end && start<n && end>=0)
            {
                ans[end] = max(ans[end], end - start + 1);
                // cout<<"start : "<<start<<endl;
                // cout<<"end : "<<end<<endl;
                // cout<<ans[end]<<endl;
            }
        }

        if (palin[i] + i > right)
        {
            center = i;
            right = palin[i] + i;
        }
    }

    for (int i : ans)
        cout << i << ' ';
    cout << endl;

    return 0;
}