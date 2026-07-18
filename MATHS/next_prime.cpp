#include <bits/stdc++.h>
using namespace std;

bool isPrime(int num)
{

    if (num == 1)
    {
        return false;
    }

    if (num == 2)
    {
        return true;
    }

    if (num % 2 == 0)
    {
        return false;
    }

    for (int i = 3; i < num; i += 2)
    {
        if (num % i == 0)
        {
            return false;
        }
    }

    return true;
}

int main()
{

    int n, t;
    cin >> t;

    vector<int> aa;

    while (t--)
    {
        cin >> n;
        aa.push_back(n);
    }

    for (int n : aa)
    {
        int x = n + 1;
        while (!isPrime(x))
            x++;
        cout << x << '\n';
    }

    return 0;
}