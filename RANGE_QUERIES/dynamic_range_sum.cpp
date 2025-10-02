#include <bits/stdc++.h>
using namespace std;

void build(long long i, long long l, long long r, long long *segmentTree, vector<long long> &a)
{
    if (l == r)
    {
        segmentTree[i] = a[l];
        return;
    }
    long long mid = l + (r - l) / 2;
    build(2 * i + 1, l, mid, segmentTree, a);
    build(2 * i + 2, mid + 1, r, segmentTree, a);
    segmentTree[i] = segmentTree[2 * i + 1] + segmentTree[2 * i + 2];
}

long long querySum(long long i, long long l, long long r, long long start, long long end, long long *segmentTree)
{
    if (end < l || r < start)
    {
        return 0;
    }
    if (start <= l && r <= end)
    {
        return segmentTree[i];
    }
    long long mid = l + (r - l) / 2;
    return querySum(2 * i + 1, l, mid, start, end, segmentTree) + querySum(2 * i + 2, mid + 1, r, start, end, segmentTree);
}

// updation in sum-segment tree
void queryUpdate(long long i, long long l, long long r, long long idx, long long value, long long *segmentTree)
{
    if (l == r)
    {
        segmentTree[i] = value;
        return;
    }
    long long mid = l + (r - l) / 2;
    if (idx <= mid)
    {
        queryUpdate(2 * i + 1, l, mid, idx, value, segmentTree);
    }
    else
    {
        queryUpdate(2 * i + 2, mid + 1, r, idx, value, segmentTree);
    }
    segmentTree[i] = segmentTree[2 * i + 1] + segmentTree[2 * i + 2];
}

int main()
{
    long long n, t;
    cin >> n >> t;
    vector<long long> a(n);
    vector<vector<long long>> q(t, vector<long long>(3, -1));

    for (long long i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    for (long long i = 0; i < t; i++)
    {
        cin >> q[i][0] >> q[i][1] >> q[i][2];
    }

    long long *segmentTree = new long long[4 * n];

    build(0, 0, n - 1, segmentTree, a);

    for (long long i = 0; i < t; i++)
    {
        long long type = q[i][0];
        if (type == 1)
        {
            long long idx = q[i][1] - 1;
            long long value = q[i][2];
            queryUpdate(0, 0, n - 1, idx, value, segmentTree);
        }
        else
        {
            long long start = q[i][1] - 1;
            long long end = q[i][2] - 1;
            cout << querySum(0, 0, n - 1, start, end, segmentTree) << endl;
        }
    }

    return 0;
}