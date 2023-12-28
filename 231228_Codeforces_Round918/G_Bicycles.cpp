#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<int, pair<int, int>> dijkType;

void solve(int test){
    int n, m; cin >> n >> m;
    vector<pair<int, int>> map[1005]; // map[u] = v, cost
    for(int i = 0; i < m; ++i){
        int u, v, w; cin >> u >> v >> w;
        map[u].push_back(make_pair(v, w));
        map[v].push_back(make_pair(u, w));
    }
    
    int s[1005];
    for(int i = 1; i <= n; ++i){
        int ss; cin >> ss;
        s[i] = ss;
    }
    
    pair<int, int> result[1005];
    for(int i = 1; i <= n; ++i){
        result[i] = make_pair(INT32_MAX, s[i]);
    }
    priority_queue < dijkType, vector<dijkType>, greater<dijkType>> heap; // cost, <u, bike>

    heap.push({0, {1, s[1]}});
    while (not heap.empty()) {
        auto p = heap.top();
        heap.pop();
        
        int cost = p.first;
        int u = p.second.first;
        int bike = p.second.second;
        
        if (result[u].first < cost and result[u].second < bike) {
            continue;
        }
        
        if (u == n) {
            cout << cost << endl;
            break;
        }
        
        for(int i = 0; i < map[u].size(); ++i){
            int v = map[u][i].first;
            int w = map[u][i].second;

            int newCost = cost + bike * w;
            int newBike = (bike < s[v]) ? bike : s[v];
            // It can be result[v].second > s[v]
            if (newCost < result[v].first or newBike < result[v].second) {
                result[v] = make_pair(newCost, newBike);
                heap.push({newCost, {v, newBike}});
            }
        }
    }
}

int main(){
    int T; cin >> T;
    for(int t = 1; t <= T; ++t){
        solve(t);
    }
    return 0;
}