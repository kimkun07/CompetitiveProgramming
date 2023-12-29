#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;

int a[200'005];

void solve(int test){
    int n; cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> a[i];
    }
    
    set<ll> diff;
    // (j+1)..i = sum[i] - sum[j]
    // condition: even in (j+1)..i == odd in (j+1)..i
    // -> even[i] - even[j] == odd[i] - odd[j]
    // -> even[j] - odd[j] == even[i] - odd[i]
    // there exists (even[j] - odd[j]) which matches (even[i] - odd[i])

    ll evenAcc = 0, oddAcc = 0;
    diff.insert(0); // sum[0]
    
    for(int i = 1; i <= n; ++i){
        if (i % 2 == 0) {
            evenAcc += a[i];
        } else {
            oddAcc += a[i];
        }
        
        const ll d = evenAcc - oddAcc;
        const bool is_in = diff.contains(d);
        if (is_in) {
            cout << "YES" << endl;
            return;
        }
        diff.insert(d);
    }
    cout << "NO" << endl;
}

int main(){
    int T; cin >> T;
    for(int t = 1; t <= T; ++t){
        solve(t);
    }
    return 0;
}