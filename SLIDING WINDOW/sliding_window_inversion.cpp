#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    vector<int> result(n - k + 1, 0);

    for (int i = 0; i < n; i++)
    {
        if (i-k+1>=0)
        {
            int ans=0;
            vector<int> temp=a;
            partition(temp,i-k+1,i,ans);
            result[i-k+1] = ans;
        }
    }
    for (int i : result)
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}