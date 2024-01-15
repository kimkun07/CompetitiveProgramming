#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;
typedef long long ll;

void solve(int testcase) {
  int n, k; cin >> n >> k;
  int eraseEffect = -1;
  int result = 0;
  for(int i = 0; i < n; ++i){
    char ch;
    cin >> ch;
    if (ch == 'B') {
      if (i <= eraseEffect) {
        continue;
      } else {
        result += 1;
        eraseEffect = i + (k - 1);
      }
    }
  }
  cout << result << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int T;
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve(t);
  }
  return 0;
}