#include <iostream>
#include <map>
#include <vector>

using namespace std;
using ll = long long;
using Pair = pair<int, int>;

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
  int n, x, y;
  cin >> n >> x >> y;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }

  // Solve
  // (a[i] + a[j]) % x == 0 and (a[i] - a[j]) % y == 0
  // => -a[j] % x == a[i] % x and a[j] % y == a[i] % y

  map<Pair, int> m;
  ll result = 0;
  for (int i = 1; i <= n; ++i) {
    auto p2 = make_pair(((-a[i] % x) + x) % x, a[i] % y);
    if (m.contains(p2)) {
      result += m.at(p2);
    }

    auto p = make_pair(a[i] % x, a[i] % y);
    if (m.contains(p)) {
      m.at(p) += 1;
    } else {
      m.insert(make_pair(p, 1));
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