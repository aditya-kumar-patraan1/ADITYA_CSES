#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll dir[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
ll M, N;

bool bfs(vector<vector<ll>> &grid, ll i, ll j, ll endX, ll endY, vector<vector<bool>> &visited, vector<vector<pair<ll,ll>>>& parent)
{
    priority_queue<vector<ll>,vector<vector<ll>>,greater<vector<ll>>> pq;
    pq.push({0,i,j});
    parent[i][j]=make_pair(-1,-1);
    visited[i][j]=true;
    while(!pq.empty()){
        ll T=pq.top()[0];
        ll i=pq.top()[1];
        ll j=pq.top()[2];
        pq.pop();
        if(i==endX && j==endY){
            return true;
        }
        for(auto t : dir){
            int i_ = i + t[0];
            int j_ = j + t[1];
            if(i_>=0 && j_>=0 && i_<M && j_<N && grid[i_][j_]!=-1 && visited[i_][j_]==false){
                visited[i_][j_]=true;
                parent[i_][j_]=make_pair(i,j);
                pq.push({T+1,i_,j_});
            }
        }
    }
    return false;
}

// DATA STRUCTURES USED :- 
// 1.) Priority Queue
// 2.) Parent 2D Vector
// 3.) Visited 2D Vector
// 4.) Result 1D Vector for tracing Path from A to B
// 5.) reverse(begin(path),end(path))

int main()
{
    ll m, n;
    cin >> m >> n;
    M = m;
    N = n;
    vector<vector<ll>> grid(m, vector<ll>(n, 0LL));
    ll startX = -1, startY = -1;
    ll endX = -1, endY = -1;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            char val;
            cin >> val;
            if (val == '.')
            {
                grid[i][j] = 0LL;
            }
            else if (val == '#')
            {
                grid[i][j] = -1LL;
            }
            else if (val == 'A')
            {
                grid[i][j] = 1LL;
                startX = i, startY = j;
            }
            else
            {
                grid[i][j] = 2LL;
                endX = i, endY = j;
            }
        }
    }
    
    
    
    // visited and parent and queue
    vector<vector<pair<ll,ll>>> parent(m,vector<pair<ll,ll>>(n));
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    
    bool ans = bfs(grid, startX, startY, endX, endY, visited, parent);
    
    if (ans)
    {
        
        cout << "YES" << endl;
        
        vector<pair<ll,ll>> result;
        ll curri=endX;
        ll currj=endY;
        
        while(curri!=-1 && currj!=-1){

            result.push_back(make_pair(curri,currj));
            pair<ll,ll> p=parent[curri][currj];
            curri=p.first;
            currj=p.second;
        }

        reverse(begin(result),end(result));
        
        cout << result.size()-1LL << endl;
        for(ll i=1;i<result.size();i++){
          ll prevX=result[i-1].first;
          ll prevY=result[i-1].second;
          ll currX=result[i].first;
          ll currY=result[i].second;
          if(currX-prevX==1){
            cout<<'D';
          }
          else if(prevX-currX==1){
            cout<<'U';
          }
          else if(prevY-currY==1){
            cout<<'L';
          }
          else{
            cout<<'R';
          }
        }
        
    }
    else
    {
        cout << "NO" << endl;
    }
    return 0;
}