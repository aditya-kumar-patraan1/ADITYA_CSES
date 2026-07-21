#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    long long sum;
    long long maxSuffix;

    Node()
    {
        sum = 0;
        maxSuffix = 0;
    }
};

void buildSegmentTree(int i, int l, int r, vector<Node> &segmentTree, vector<long long> &nums)
{
    if (l == r)
    {
        segmentTree[i].sum = nums[l];
        segmentTree[i].maxSuffix = nums[l];
        return;
    }

    int mid = l + (r - l) / 2;

    buildSegmentTree(2 * i + 1, l, mid, segmentTree, nums);
    buildSegmentTree(2 * i + 2, mid + 1, r, segmentTree, nums);

    segmentTree[i].sum = segmentTree[2 * i + 1].sum + segmentTree[2 * i + 2].sum;

    segmentTree[i].maxSuffix = max({segmentTree[2 * i + 1].maxSuffix,
                                    segmentTree[2 * i + 1].sum + segmentTree[2 * i + 2].maxSuffix,
                                    segmentTree[2 * i + 1].sum});
}

void pointUpdateQuery(int i, int l, int r, int idx, long long val, vector<Node> &segmentTree)
{
    if (l == r)
    {
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

    segmentTree[i].sum = segmentTree[2 * i + 1].sum + segmentTree[2 * i + 2].sum;

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

    if(leftAns.maxSuffix == LLONG_MIN){
        return rightAns;
    }
    
    if(rightAns.maxSuffix == LLONG_MIN){
        return leftAns;
    }
    
    Node temp;

    temp.maxSuffix = max(leftAns.maxSuffix,leftAns.sum + rightAns.maxSuffix);
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

    vector<array<int, 3>> q;

    for (int i = 0; i < m; i++)
    {
        int option;
        int l;
        int r;
        cin >> option >> l >> r;
        l--, r--;
        q.push_back({option, l, r});
    }

    for (int i = 0; i < m; i++)
    {
        int option = q[i][0];
        // int l = q[i][1];
        // cout << "option : " << option << endl;
        if (option == 1)
        {
            // cout << "index : " << q[i][1] << endl;
            // cout << "val : " << q[i][2] + 1 << endl;
            pointUpdateQuery(0, 0, n - 1, q[i][1], q[i][2] + 1, segmentTree);
        }
        else
        {
            // cout << "l : " << q[i][1] << endl;
            // cout << "r : " << q[i][2] << endl;
            cout << max(0LL,maxSumQuery(0, 0, n - 1, q[i][1], q[i][2], segmentTree).maxSuffix) << '\n';
        }
    }

    return 0;
}