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

void solve(int testcase) {
  int n;
  cin >> n;
  int first = n + 1, last = 0;
  for (int i = 1; i <= n; ++i) {
    char c;
    cin >> c;
    switch (c) {
    case 'W':
      break;
    case 'B':
      first = min(first, i);
      last = max(last, i);
      break;
    }
  }
  int result = last - first + 1;
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