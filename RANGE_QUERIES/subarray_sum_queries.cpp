#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    long long sum;
    long long prefEnding;
    long long prefNotEndingButMax;
    long long maxSuffix;

    Node()
    {
        sum = 0;
        prefEnding = 0;
        prefNotEndingButMax = 0;
        maxSuffix = 0;
    }
};

void buildSegmentTree(int i, int l, int r, vector<Node> &segmentTree, vector<long long> &nums)
{
    if (l == r)
    {
        segmentTree[i].prefEnding = nums[l];
        segmentTree[i].prefNotEndingButMax = 0;
        segmentTree[i].sum = nums[l];
        segmentTree[i].maxSuffix = nums[l];
        return;
    }

    int mid = l + (r - l) / 2;

    buildSegmentTree(2 * i + 1, l, mid, segmentTree, nums);
    buildSegmentTree(2 * i + 2, mid + 1, r, segmentTree, nums);

    segmentTree[i].prefEnding = max({segmentTree[2 * i + 2].prefEnding,
                                     segmentTree[2 * i + 2].sum + segmentTree[2 * i + 1].prefEnding});

    segmentTree[i].sum = segmentTree[2 * i + 1].sum + segmentTree[2 * i + 2].sum;

    segmentTree[i].prefNotEndingButMax = max({
        segmentTree[2 * i + 2].prefNotEndingButMax,
        segmentTree[2 * i + 1].prefEnding,
        segmentTree[2 * i + 1].prefNotEndingButMax,
        segmentTree[2 * i + 1].sum,
        max(segmentTree[2 * i + 1].sum, segmentTree[2 * i + 1].prefEnding) + segmentTree[2 * i + 2].maxSuffix});

    segmentTree[i].maxSuffix = max({
        segmentTree[2 * i + 1].maxSuffix,
        segmentTree[2 * i + 1].sum + segmentTree[2 * i + 2].maxSuffix,
        segmentTree[2 * i + 1].sum});
}

void pointUpdateQuery(int i, int l, int r, int idx, long long val, vector<Node> &segmentTree)
{
    if (l == r)
    {
        segmentTree[i].prefEnding = val;
        segmentTree[i].prefNotEndingButMax = 0;
        segmentTree[i].sum = val;
        segmentTree[i].maxSuffix = val;
        return;
    }

    int mid = l + (r - l) / 2;

    if (idx <= mid)
    {
        pointUpdateQuery(2 * i + 1, l, mid, idx, val, segmentTree);
    }
    else
    {
        pointUpdateQuery(2 * i + 2, mid + 1, r, idx, val, segmentTree);
    }

    segmentTree[i].prefEnding = max({segmentTree[2 * i + 2].prefEnding,
                                     segmentTree[2 * i + 2].sum + segmentTree[2 * i + 1].prefEnding});

    segmentTree[i].sum = segmentTree[2 * i + 1].sum + segmentTree[2 * i + 2].sum;

    segmentTree[i].prefNotEndingButMax = max({
        segmentTree[2 * i + 2].prefNotEndingButMax,
        segmentTree[2 * i + 1].prefEnding,
        segmentTree[2 * i + 1].prefNotEndingButMax,
        segmentTree[2 * i + 1].sum,
        max(segmentTree[2 * i + 1].sum, segmentTree[2 * i + 1].prefEnding) + segmentTree[2 * i + 2].maxSuffix});

    segmentTree[i].maxSuffix = max({
        segmentTree[2 * i + 1].maxSuffix,
        segmentTree[2 * i + 1].sum + segmentTree[2 * i + 2].maxSuffix,
        segmentTree[2 * i + 1].sum});
}

long long maxSumQuery(int i, int l, int r, int start, int end, vector<Node> &segmentTree)
{
    if (end < l || r < start)
    {
        return 0;
    }

    if (start <= l && r <= end)
    {
        return max({segmentTree[i].sum,
                    segmentTree[i].prefEnding,
                    segmentTree[i].prefNotEndingButMax,
                    segmentTree[i].maxSuffix});
    }

    int mid = l + (r - l) / 2;

    long long rightAns = maxSumQuery(2 * i + 2, mid + 1, r, start, end, segmentTree);

    return rightAns;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<long long> nums(n);

    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    vector<Node> segmentTree(4 * n);

    buildSegmentTree(0, 0, n - 1, segmentTree, nums);

    vector<array<long long, 2>> q;

    for (int i = 0; i < m; i++)
    {
        int k;
        long long x;
        cin >> k >> x;
        k--;
        q.push_back({k, x});
    }

    for (int i = 0; i < m; i++)
    {
        int k = q[i][0];
        long long x = q[i][1];

        pointUpdateQuery(0, 0, n - 1, k, x, segmentTree);

        cout << maxSumQuery(0, 0, n - 1, 0, n - 1, segmentTree) << '\n';
    }

    return 0;
}