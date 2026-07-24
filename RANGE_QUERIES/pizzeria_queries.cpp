#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void buildSegmentTree(int i, int l, int r, vector<ll> &segmentTree, vector<int> &nums, int deduct)
{
    if (l == r)
    {
        segmentTree[i] = nums[l] + abs(l - deduct);
        return;
    }
    int mid = l + (r - l) / 2;
    buildSegmentTree(2 * i + 1, l, mid, segmentTree, nums, deduct);
    buildSegmentTree(2 * i + 2, mid + 1, r, segmentTree, nums, deduct);
    segmentTree[i] = min(segmentTree[2 * i + 1], segmentTree[2 * i + 2]);
}

void pointUpdateQuery(int i, int l, int r, ll idx, ll val, ll deduct, vector<ll> &segmentTree)
{
    if (l == r)
    {
        segmentTree[i] = val + abs(l - deduct);
        return;
    }
    ll mid = l + (r - l) / 2;

    if (idx <= mid)
    {
        pointUpdateQuery(2 * i + 1, l, mid, idx, val, deduct, segmentTree);
    }
    else
    {
        pointUpdateQuery(2 * i + 2, mid + 1, r, idx, val, deduct, segmentTree);
    }

    segmentTree[i] = min(segmentTree[2 * i + 1], segmentTree[2 * i + 2]);
}

ll maxSumQuery(int i, int l, int r, int start, int end, vector<ll> &segmentTree)
{
    if (end < l || r < start)
    {
        return LLONG_MAX;
    }
    if (start <= l && r <= end)
    {
        return segmentTree[i];
    }
    int mid = l + (r - l) / 2;
    ll leftAns = maxSumQuery(2 * i + 1, l, mid, start, end, segmentTree);
    ll rightAns = maxSumQuery(2 * i + 2, mid + 1, r, start, end, segmentTree);

    return min(leftAns, rightAns);
}

int main()
{

    ll n, q;
    cin >> n >> q;

    vector<int> nums(n, -1);

    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    vector<vector<ll>> queries;

    for (int i = 0; i < q; i++)
    {
        ll option;
        cin >> option;
        if (option == 1)
        {
            ll k, x;
            cin >> k >> x;
            k--;
            queries.push_back({1, k, x});
        }
        else
        {
            ll k;
            cin >> k;
            k--;
            queries.push_back({2, k});
        }
    }

    vector<ll> segmentTreeFromRight(4 * n,LLONG_MAX), segmentTreeFromLeft(4 * n,LLONG_MAX);

    buildSegmentTree(0, 0, n - 1, segmentTreeFromLeft, nums, 0);
    buildSegmentTree(0, 0, n - 1, segmentTreeFromRight, nums, n - 1);

    for (int i = 0; i < q; i++)
    {
        ll option = queries[i][0];
        if (option == 1)
        {

            // changing in segment Tree

            ll kth = queries[i][1];
            ll newPrice = queries[i][2];

            // int i, int l, int r, ll idx, ll val, ll deduct, vector<ll> &segmentTree
            pointUpdateQuery(0, 0, n - 1, kth, newPrice, 0, segmentTreeFromLeft);
            pointUpdateQuery(0, 0, n - 1, kth, newPrice, n-1, segmentTreeFromRight);
        }
        else
        {
            ll kth = queries[i][1];
            ll case1 = maxSumQuery(0, 0, n - 1, 0, kth, segmentTreeFromRight) - (n - kth - 1);
            ll case2 = maxSumQuery(0,0,n-1,kth+1,n-1,segmentTreeFromLeft) - kth;
            cout<<min(case1,case2)<<endl;
        }
    }

    return 0;
}
