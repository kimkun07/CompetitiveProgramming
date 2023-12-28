#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

bool isV(char c) {
    return (c == 'a' or c == 'e');
}
bool isC(char c) {
    return (not isV(c));
}

void solve(int test){
    int n;
    cin >> n;
    string word;
    cin >> word;
    
    for(int i = 0; i < n;){
        // C V C V -> C V . C V
        // C V C C -> C V C . C
        
        // i should be C
        // i + 1 should be V
        if (i + 2 == n) {
            cout << word.substr(i, 2); // C V NULL
            break;
        }
        // i + 2 should be C
        if (i + 3 == n) {
            cout << word.substr(i, 3); // C V C NULL
            break;
        }
        if (isV(word.at(i + 3))) {
            cout << word.substr(i, 2) << "."; // C V . C V
            i += 2;
        } else {
            cout << word.substr(i, 3) << "."; // C V C . C
            i += 3;
        }
    }
    cout << endl;
}

int main(){
    int T; cin >> T;
    for(int t = 1; t <= T; ++t){
        solve(t);
    }
    return 0;
}