#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

void printAns(bool yes) {
  if (yes) {
    cout << "Yes"
         << "\n";
  } else {
    cout << "No"
         << "\n";
  }
}

char decode(char enc) { return (enc - 1) + 'a'; }

void solve(int testcase) {
  int n;
  cin >> n;
  n = n - 3; // 'a' 'a' 'a'
  int third = min(25, n) + 1;
  n = max(n - 25, 0);
  int second = min(25, n) + 1;
  n = max(n - 25, 0);
  int first = min(25, n) + 1;
  cout << decode(first) << decode(second) << decode(third) << "\n";
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