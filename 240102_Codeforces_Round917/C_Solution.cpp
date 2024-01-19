// Solution from 238743155

#include <bits/stdc++.h>

using namespace std;

void solve() {
  int n, k, s;
  cin >> n >> k >> s;
  vector<int> a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];

  vector<int> b(k);
  for (int i = 0; i < k; i++)
    cin >> b[i];

  int ans = 0;
  for (int i = 0; i < s && i <= 2 * n; i++) {
    int cur = 0;
    for (int j = 0; j < n; j++) {
      cur += (a[j] == j + 1);
    }
    cur += (s - i - 1) / 2;
    if (cur > ans) {
      ans = cur;
    }
    for (int j = 0; j < b[i % k]; j++) {
      a[j]++;
    }
  }
  cout << ans << endl;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}