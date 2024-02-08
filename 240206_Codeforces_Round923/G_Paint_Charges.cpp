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

void update(int &to, int value) {
  if (to == -1) {
    to = value;
  }
  to = min(to, value);
}

void solve(int testcase) {
  int n;
  cin >> n;

  vector<int> a(n + 1); // 1..n
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }

  // Reason
  // We only need j and k for expressing a state.
  //    i:
  //    j: leftmost unpainted (1..n+1)
  //    k: rightmost painted  (0..n)
  // Because i is increasing, tile at j+1..k is meaningless.
  // One should paint j..i or i..k..r to be meaningful.

  // [1..n][1..n+1][1..n]
  vector<vector<vector<int>>> dp(
      n + 1, vector<vector<int>>(n + 2, vector<int>(n + 1, -1)));

  dp[0][1][0] = 0; // Empty
  // dp[1][1][0] = 0;           // no paint
  // dp[1][1][1] = 1;           // paint left
  // dp[1][a[1] + 1][a[1]] = 1; // paint right

  for (int i = 0; i < n; ++i) {
    // a[i] is already painted
    // whether to paint a[i + 1] at position (i + 1) in each state
    int pos = i + 1;
    int paintCharge = a[i + 1];
    for (int j = 1; j <= n + 1; ++j) {
      for (int k = 0; k <= n; ++k) {
        if (dp[i][j][k] == -1) {
          // unreachable state
          continue;
        }

        // paint left: l..pos
        int l = pos - paintCharge + 1;
        int nextK = (k < pos) ? pos : k; // pos could be rightmost paint
        int nextJ = (l <= j and j <= pos) ? (nextK + 1)
                                          : j; // if l..pos was unpainted j
        update(dp[i + 1][min(nextJ, n + 1)][min(nextK, n)], dp[i][j][k] + 1);

        // paint right: pos..r
        int r = pos + paintCharge - 1;
        nextK = (k < r) ? r : k; // r could be rightmost paint
        nextJ = (pos <= j and j <= r) ? (nextK + 1)
                                      : j; // if pos..r was unpainted j
        update(dp[i + 1][min(nextJ, n + 1)][min(nextK, n)], dp[i][j][k] + 1);

        // do not paint
        update(dp[i + 1][j][k], dp[i][j][k]);
      }
    }
  }

  cout << dp[n][n + 1][n] << "\n";
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