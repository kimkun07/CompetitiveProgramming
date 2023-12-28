#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;

void solve(int test){
    int n; cin >> n;
    ll sum = 0;
    ll temp;
    for(int i = 0; i < n; ++i){
        cin >> temp;
        sum += temp;
    }
    
    double root = sqrt(sum);
    ll nearby = root;
    
    string result = "NO";
    if (nearby * nearby == sum) {
        result = "YES";
    } else {
        ++nearby;
        if (nearby * nearby == sum) {
            result = "YES";
        }
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