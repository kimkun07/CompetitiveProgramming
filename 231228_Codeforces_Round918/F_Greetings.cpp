#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

void solve(int test){
    int n; cin >> n;
    vector<pair<int, int>> infos;
    for(int i = 0; i < n; ++i){
        int a, b; cin >> a >> b;
        infos.push_back(make_pair(a, b));
    }
    
    // greet++ iff a[i] < a[j] < b[j] < b[i]
    sort(infos.begin(), infos.end());
    // now find all (i < j and b[i] > b[j])
    // when inserting b[j], find how many is bigger than itself
    vector<int> bs;
    ll result = 0;
    for(int i = 0; i < n; ++i){
        int b = infos[i].second;
        // binary search
        vector<int>::const_iterator itr = lower_bound(bs.cbegin(), bs.cend(), b);
        int bigger = bs.cend() - itr;
        result += bigger;
        
        bs.insert(itr, b);
    }
    
    cout << result << endl;
}

int main(){
    int T; cin >> T;
    for(int t = 1; t <= T; ++t){
        solve(t);
    }
    return 0;
}