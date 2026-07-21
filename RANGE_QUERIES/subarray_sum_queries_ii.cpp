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

    segmentTree[i].prefNotEndingButMax = max({segmentTree[2 * i + 2].prefNotEndingButMax,
                                              segmentTree[2 * i + 1].prefEnding,
                                              segmentTree[2 * i + 1].prefNotEndingButMax,
                                              segmentTree[2 * i + 1].sum,
                                              max(segmentTree[2 * i + 1].sum, segmentTree[2 * i + 1].prefEnding) + segmentTree[2 * i + 2].maxSuffix});

    segmentTree[i].maxSuffix = max({segmentTree[2 * i + 1].maxSuffix,
                                    segmentTree[2 * i + 1].sum + segmentTree[2 * i + 2].maxSuffix,
                                    segmentTree[2 * i + 1].sum});
}

Node maxSumQuery(int i, int l, int r, int start, int end, vector<Node> &segmentTree)
{
    if (end < l || r < start)
    {
        Node temp;
        temp.maxSuffix = LLONG_MIN;
        temp.prefEnding = LLONG_MIN;
        temp.prefNotEndingButMax = LLONG_MIN;
        temp.sum = 0;
        return temp;
    }

    if (start <= l && r <= end)
    {
        return segmentTree[i];
    }

    int mid = l + (r - l) / 2;

    Node leftAns = maxSumQuery(2 * i + 1, l, mid, start, end, segmentTree);
    Node rightAns = maxSumQuery(2 * i + 2, mid + 1, r, start, end, segmentTree);

    if (leftAns.maxSuffix == LLONG_MIN)
        return rightAns;
    if (rightAns.maxSuffix == LLONG_MIN)
        return leftAns;

    Node temp;
    temp.maxSuffix = max({leftAns.maxSuffix, leftAns.sum + rightAns.maxSuffix, leftAns.sum});
    temp.prefEnding = max({rightAns.prefEnding, rightAns.sum + leftAns.prefEnding});
    temp.prefNotEndingButMax = max({leftAns.sum, leftAns.prefEnding, leftAns.prefNotEndingButMax, rightAns.prefNotEndingButMax, max(leftAns.prefEnding, leftAns.sum) + rightAns.maxSuffix});
    temp.sum = leftAns.sum + rightAns.sum;

    return temp;
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

    vector<array<int, 2>> q;

    for (int i = 0; i < m; i++)
    {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        q.push_back({l, r});
    }

    for (int i = 0; i < m; i++)
    {
        int l = q[i][0];
        int r = q[i][1];

        Node ansNode = maxSumQuery(0, 0, n - 1, l, r, segmentTree);
        
        long long ans = ansNode.maxSuffix;
        ans=max(ans,ansNode.prefEnding);
        ans=max(ans,ansNode.prefNotEndingButMax);
        ans=max(ans,ansNode.sum);

        cout << max(0LL,ans) << '\n';
    }

    return 0;
}