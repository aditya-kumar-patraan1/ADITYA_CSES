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
        int mirror = 2 * center - i;

        if (right > i)
        {
            palin[i] = min(palin[mirror], right - i);
        }

        int a = i + (palin[i] + 1);
        int b = i - (palin[i] + 1);

        while (b >= 0 && a < newSize && modifiedS[a] == modifiedS[b])
        {
            palin[i]++;
            a++;
            b--;
        }

        if (palin[i] + i > right)
        {
            center = i;
            right = palin[i] + i;
        }
    }

    int e_i = 0;
    int s_i = 0;

    for (int i = 0; i < newSize; i++)
    {
        int start = (i - palin[i]) / 2;
        int end = (i + palin[i]) / 2 - 1;

        if (start >= 0 && end < n)
        {
            if(end - start + 1 > e_i - s_i + 1){
                s_i = start;
                e_i = end;
            }
        }
    }

    string ans="";
    for(int i=s_i;i<=e_i;i++) ans+=s[i];
    cout<<ans<<endl;
    
    return 0;
}