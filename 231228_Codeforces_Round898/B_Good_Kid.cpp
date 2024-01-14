#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;
typedef long long ll;

void solve(int testcase) {
  int n;
  cin >> n;
  vector<int> a;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    auto it = lower_bound(a.begin(), a.end(), x);
    a.insert(it, x);
  }
  a[0] += 1;

  auto lama = [](const int &acc, const int &e) -> int { return acc * e; };
  int result = accumulate(a.begin(), a.end(), 1, lama);
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