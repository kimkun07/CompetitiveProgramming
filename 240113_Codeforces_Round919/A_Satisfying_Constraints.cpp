#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;
typedef long long ll;

void solve(int testcase) {
  int n;
  cin >> n;

  int lower = 0, upper = INT_MAX;
  vector<int> exclude;
  for (int i = 0; i < n; ++i) {
    int a, x;
    cin >> a >> x;
    switch (a) {
    case 1:
      lower = max(lower, x);
      break;
    case 2:
      upper = min(upper, x);
      break;
    default:
      auto it = upper_bound(exclude.begin(), exclude.end(), x);
      exclude.insert(it, x);
      break;
    }
  }
  auto upperIt = upper_bound(exclude.begin(), exclude.end(), upper);
  auto lowerIt = lower_bound(exclude.begin(), exclude.end(), lower);
  cout << max(0, upper - lower + 1) - (upperIt - lowerIt) << "\n";
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