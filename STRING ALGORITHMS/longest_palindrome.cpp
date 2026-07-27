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

    int newSize = 2 * n + 1;

    vector<int> palin(newSize);

    int right = 0, center = 0;

    for (int i = 0; i < newSize; i++)
    {
        int center = 2 * center - i;

        if (right > i)
        {
            palin[i] = min(center, right - i);
        }

        int a = palin[i] + (i + 1);
        int b = palin[i] - (i + 1);

        while (b >= 0 && a < newSize && modifiedS[a] == modifiedS[b])
        {
            palin[i]++;
            a++;
            b--;
        }

        if (palin[i] + i > center)
        {
            center = i;
            right = palin[i] + i;
        }
    }

    return 0;
}