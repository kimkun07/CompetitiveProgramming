#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int a[200'005];
ll odd[200'005], even[200'005];

void solve(int test){
    int n; cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> a[i];
    }
    
    for(int i = 1; i <= n; ++i){
        even[i] = odd[i] = 0;
        for(int j = 1; j <= i; ++j){
            if (i % 2 == 0) {
                even[j] += a[i];
            } else {
                odd[j] += a[i];
            }
            if (even[j] == odd[j]) {
                cout << "YES" << endl;
                return;
            }
        }
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