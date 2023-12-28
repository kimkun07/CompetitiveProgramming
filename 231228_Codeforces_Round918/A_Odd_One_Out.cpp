#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

void solve(int test){
    int a, b, c;
    cin >> a >> b >> c;
    int result = a ^ b ^ c;
    cout << result << endl;
}

int main(){
    int T; cin >> T;
    for(int t = 1; t <= T; ++t){
        solve(t);
    }
    return 0;
}