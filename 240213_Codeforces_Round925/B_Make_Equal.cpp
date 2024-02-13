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
  vector<int> a(n + 1);
  ll sum = 0LL;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i]; // (sum of a[i]) % n == 0
    sum += a[i];
  }

  ll target = sum / n;
  ll reserve = 0;
  for (int i = 1; i <= n; ++i) {
    ll need = target - a[i];
    if (need > reserve) {
      printAns(false);
      return;
    }
    reserve -= need;
  }

  printAns(true);
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