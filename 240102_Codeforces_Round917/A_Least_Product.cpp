#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

void solve(int test){
    int n; cin >> n;
    int a[105];
    for(int i = 1; i <= n; ++i){
        cin >> a[i];
    }
    
    // abs(product) cannot be bigger.
    int sign = 1;
    for(int i = 1; i <= n; ++i){
        if (a[i] > 0) {
            sign *= 1;
        } else if (a[i] == 0) {
            sign *= 0;
        } else {
            sign *= -1;
        }
    }
    
    if (sign <= 0) {
        cout << 0 << endl;
    } else {
        cout << 1 << endl;
        cout << "1 0" << endl;
    }
}

int main(){
    int T; cin >> T;
    for(int t = 1; t <= T; ++t){
        solve(t);
    }
    return 0;
}