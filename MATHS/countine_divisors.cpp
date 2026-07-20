#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;

    vector<int> aa;

    while (t > 0)
    {
        int n;
        cin >> n;
        aa.push_back(n);
        t -= 1;
    }

    for (int n : aa)
    {
        int c = 0;

        for (int i = 1; i * i <= n; i++)
        {
            if (n % i == 0)
            {
                c++;
                if (n / i != i)
                {
                    c++;
                }
            }
        }

        cout << c << endl;
    }

    return 0;
}