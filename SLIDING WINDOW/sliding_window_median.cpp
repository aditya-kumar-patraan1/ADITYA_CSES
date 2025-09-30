#include <bits/stdc++.h>
using namespace std;

multiset<int> maxHeap,minHeap;

void balance(){
    if(maxHeap.size()>minHeap.size()+1){
        minHeap.insert(*maxHeap.rbegin());
        maxHeap.erase(prev(maxHeap.end()));
    }
    if(minHeap.size()>maxHeap.size()+1){
        maxHeap.insert(*minHeap.begin());
        minHeap.erase(minHeap.begin());
    }
}

void erase(int element){
    if(!maxHeap.empty() && element<=*maxHeap.rbegin()){
        //element is present in first maxHeap so remove it from that one maxHeap
        auto it = maxHeap.find(element);
        if(it!=maxHeap.end()) maxHeap.erase(it);
    }
    else{
        auto it = minHeap.find(element);
        if(it!=minHeap.end()) minHeap.erase(it);
    }
}

int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    vector<int> A(n);
    for(int i = 0; i < n; i++) cin >> A[i];

    vector<int> result(n-k+1,0);
    multiset<int> ms;

    for(int i=0;i<n;i++){
        maxHeap.insert(A[i]);
        if(!maxHeap.empty() && !minHeap.empty() && *maxHeap.rbegin()>*minHeap.begin()){
            minHeap.insert(*maxHeap.rbegin());
            maxHeap.erase(prev(maxHeap.end()));
        }
        balance();
        if(i>=k-1){
            if(minHeap.size() == maxHeap.size()){
                result[i-k+1]=*maxHeap.rbegin();               // selecting the smaller one
            }
            else{
                result[i-k+1]=(maxHeap.size()>minHeap.size()?*maxHeap.rbegin():*minHeap.begin());
            }
            int element=A[i-k+1];
            erase(element);
            balance();
        }
    }




    for(int x : result) cout << x << " ";
    cout << endl;
    
    return 0;
}