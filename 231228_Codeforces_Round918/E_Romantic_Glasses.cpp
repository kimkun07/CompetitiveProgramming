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

    even[0] = odd[0] = 0;
    for(int i = 1; i <= n; ++i){
        even[i] = even[i - 1];
        odd[i] = odd[i - 1];
        if (i % 2 == 0) {
            even[i] += a[i];
        } else {
            odd[i] += a[i];
        }
    }
    
    // (j+1)..i
    for(int i = 1; i <= n; ++i){
        for(int j = 0; j < i; ++j){
            if (even[i] - even[j] == odd[i] - odd[j]) {
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