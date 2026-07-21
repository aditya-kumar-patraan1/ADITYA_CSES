#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int sum;
    int prefEnding;
    int prefNotEndingButMax;

    Node()
    {
        this->sum = 0;
        this->prefEnding = 0;
        this->prefNotEndingButMax = 0;
    }
};

void buildSegmentTree(int i, int l, int r, vector<Node> &segmentTree, vector<int> &nums)
{
    if (l == r)
    {
        segmentTree[i].prefEnding = nums[l];
        segmentTree[i].prefNotEndingButMax = 0;
        segmentTree[i].sum = nums[l];
        return;
    }

    int mid = l + (r - l) / 2;

    buildSegmentTree(2 * i + 1, l, mid, segmentTree, nums);
    buildSegmentTree(2 * i + 2, mid + 1, r, segmentTree, nums);

    segmentTree[i].prefEnding = max({segmentTree[2 * i + 2].prefEnding, segmentTree[2 * i + 2].sum + segmentTree[2 * i + 1].prefEnding});
    segmentTree[i].sum = segmentTree[2 * i + 1].sum + segmentTree[2 * i + 2].sum;
    segmentTree[i].prefNotEndingButMax = max({segmentTree[2 * i + 2].prefNotEndingButMax, segmentTree[2 * i + 1].prefEnding, segmentTree[2 * i + 1].prefNotEndingButMax, segmentTree[2 * i + 1].sum});
}

void pointUpdateQuery(int i, int l, int r, int idx, int val, vector<Node> &segmentTree)
{
    if (l == r)
    {
        segmentTree[i].prefEnding = val;
        segmentTree[i].prefNotEndingButMax = 0;
        segmentTree[i].sum = val;
        return;
    }

    int mid = l + (r - l) / 2;

    if (idx <= mid)
    {
        // move left
        pointUpdateQuery(2 * i + 1, l, mid, idx, val, segmentTree);
    }
    else
    {
        pointUpdateQuery(2 * i + 2, mid + 1, r, idx, val, segmentTree);
    }

    segmentTree[i].prefEnding = max({segmentTree[2 * i + 2].prefEnding, segmentTree[2 * i + 2].sum + segmentTree[2 * i + 1].prefEnding});
    segmentTree[i].sum = segmentTree[2 * i + 1].sum + segmentTree[2 * i + 2].sum;
    segmentTree[i].prefNotEndingButMax = max({segmentTree[2 * i + 2].prefNotEndingButMax, segmentTree[2 * i + 1].prefEnding, segmentTree[2 * i + 1].prefNotEndingButMax, segmentTree[2 * i + 1].sum});
}

int maxSumQuery(int i, int l, int r, int start, int end, vector<Node> &segmentTree)
{

    if (end < l || r < start)
    {
        return 0;
    }

    if (start <= l && r <= end)
    {
        return max({segmentTree[i].sum, segmentTree[i].prefEnding, segmentTree[i].prefNotEndingButMax});
    }

    int mid = l + (r - l) / 2;
    cout<<"mid : "<<mid<<endl;

    int rightAns = maxSumQuery(2 * i + 2, mid + 1, r, start, end, segmentTree);

    return rightAns;
}

int main()
{

    int n, m;
    cin >> n >> m;

    vector<int> nums(n);

    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    vector<Node> segmentTree(4 * n);

    buildSegmentTree(0, 0, n - 1, segmentTree, nums);

    vector<array<int, 2>> q;

    for (int i = 0; i < m; i++)
    {
        int k, x;
        cin >> k >> x;
        k--;
        q.push_back({k, x});
    }

    // cout<<"Overall : "<<maxSumQuery(0, 0, n - 1, 0, n - 1, segmentTree)<<endl;

    for (int i = 0; i < m; i++)
    {
        int k = q[i][0];
        int x = q[i][1];
        // cout<<"for k : "<<k<<" and x : "<<x<<endl;
        // cout<<"calling pointUpdateQuery..."<<endl;
        // i,l,r,idx,val,segmentTree
        pointUpdateQuery(0, 0, n - 1, k, x, segmentTree);
        // i,0,n-1,0,n-1,segmentTree
        // cout<<"calling maxSumQuery..."<<endl;
        cout << maxSumQuery(0, 0, n - 1, 0, n - 1, segmentTree) << endl;
    }

    return 0;
}
