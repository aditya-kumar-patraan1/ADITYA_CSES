#include <bits/stdc++.h>
using namespace std;

#define int long long

void queryOnePointUpdate(int i, int l, int r, int pos, int val, int *segmentTree)
{
    if (l == r)
    {
        segmentTree[i] += val;
        return;
    }
    int mid = l + (r - l) / 2;
    if (pos <= mid)
    {
        queryOnePointUpdate(2 * i + 1, l, mid, pos, val, segmentTree);
    }
    else
    {
        queryOnePointUpdate(2 * i + 2, mid + 1, r, pos, val, segmentTree);
    }
    segmentTree[i] = segmentTree[2 * i + 1] + segmentTree[2 * i + 2];
}

int querySum(int i, int l, int r, int start, int end, int *segmentTree)
{
    if(end<l || r<start){
        return 0;
    }
    if(start<=l && r<=end){
        return segmentTree[i];
    }
    
    int mid=l+(r-l)/2;

    return querySum(2*i+1,l,mid,start,end,segmentTree) + querySum(2*i+2,mid+1,r,start,end,segmentTree);

}

#undef int

int main()
{
    long long n, k;
    cin >> n >> k;
    vector<long long> a(n, 0);
    vector<int> comp(n, 0);
    for (long long i = 0; i < n; i++)
    {
        cin >> a[i];
        comp[i] = a[i];
    }

    // i compressed the values of each a[i]
    sort(begin(comp), end(comp));
    comp.erase(unique(begin(comp), end(comp)), end(comp));

    for (long long i = 0; i < n; i++)
    {
        a[i] = lower_bound(begin(comp), end(comp), a[i]) - begin(comp);
    }

    long long sz = comp.size();
    long long N = sz * 4LL;

    long long *segmentTree = new long long[N];

    // considering the first window only
    long long cntInversion = 0;
    for (long long i = 0; i < k; i++)
    {
        long long pos = a[i];
        queryOnePointUpdate(0, 0, sz - 1, pos, 1, segmentTree);
        cntInversion += querySum(0, 0, sz - 1, pos + 1, sz - 1, segmentTree);
    }

    vector<long long> ans;

    ans.push_back(cntInversion);

    for (long long i = k; i < n; i++)
    {
        long long prevPos = a[i - k];
        queryOnePointUpdate(0, 0, sz - 1, prevPos, -1, segmentTree); // reducing the frequency of that element
        cntInversion -= querySum(0, 0, sz - 1, 0, prevPos - 1, segmentTree);
        long long currPos = a[i];
        queryOnePointUpdate(0, 0, sz - 1, currPos, 1, segmentTree); // adding the frequency of that element in the segment Tree
        cntInversion += querySum(0, 0, sz - 1, currPos + 1, sz - 1, segmentTree);
        ans.push_back(cntInversion);
    }

    for (long long i : ans)
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}