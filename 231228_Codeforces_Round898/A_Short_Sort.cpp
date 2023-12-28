#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

void solve(int test){
    string s;
    cin >> s;
    char a = s[0];
    char b = s[1];
    char c = s[2];
    
    int count = (a == 'a') + (b == 'b') + (c == 'c');
    string result = ((count == 3) or (count == 1)) ? "YES" : "NO";
    cout << result << endl;
}

int main(){
    int T; cin >> T;
    for(int t = 1; t <= T; ++t){
        solve(t);
    }
    return 0;
}