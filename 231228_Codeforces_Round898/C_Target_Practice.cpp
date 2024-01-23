#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;
typedef long long ll;

void solve(int testcase) {
  int result = 0;
  for (int r = 1; r <= 10; ++r) {
    for (int c = 1; c <= 10; ++c) {
      char ch;
      cin >> ch;
      if (ch == '.') {
        continue;
      }

      int left = c;
      int right = 11 - c;
      int top = r;
      int bottom = 11 - r;
      int score = min(left, min(right, min(top, bottom)));
      result += score;
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