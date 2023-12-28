#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;

void solve(int test){
    char square[3][3]; // Don't need NUL
    scanf("%s", square[0]);
    scanf("%s", square[1]);
    scanf("%s", square[2]);
    
    char result = '*';
    int count[3] = {0};
    int flag = false;
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if (not (square[i][j] == '?')) {
                ++count[square[i][j] - 'A'];
            } else {
                flag = true;
            }
        }
        if (flag) {
            for(int j = 0; j < 3; ++j){
                if (count[j] != (i + 1)) {
                    result = j + 'A';
                }
            }
            flag = false;
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