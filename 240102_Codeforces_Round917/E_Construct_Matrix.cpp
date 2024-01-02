#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

void solve(int test){
    int n, k; cin >> n >> k;
    if (k % n == 0) {
        const int onePerRow = k / n;
        cout << "Yes" << endl;
        for(int i = 0; i < n; ++i){
            // 1 1 1 0 0 0 ... 0
            for(int j = 0; j < n; ++j){
                const int num = ((i + j) % n < onePerRow);
                printf("%d ", num);
            }
            cout << endl;
        }
    } else {
        cout << "No" << endl;
    }
}

int main(){
    int T; cin >> T;
    for(int t = 1; t <= T; ++t){
        solve(t);
    }
    return 0;
}