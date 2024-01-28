#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
ll MOD = 998'244'353;

void printAns(bool yes) {
  if (yes) {
    cout << "Yes"
         << "\n";
  } else {
    cout << "No"
         << "\n";
  }
}

ll addMod(ll &a, ll &b) { return (a + b) % MOD; }

void solve(int testcase) {
  int n, k;
  cin >> n >> k;

  // Solve
  // 1. Convert binary string into array of ints.
  //    `1` will split zero into arrays.
  //    ex) 000110000 can be represented as [3, 0, 4]
  //    Then a[i] + 1 + a[i + 1] <= k (length of substring 00...1..00 <= k)
  //    Sum of (a[i] + 1) * (a[i+1] + 1) == num (substring number of cases)
  // 2. Solve as DP[sum][last]
  //    DP[sum][last]: number of cases for a
  //    sum = a's current sum, last = last number of a
  //    (length of a doesn't matter)
  // 3. [sum-delta][x] -> [sum][last]
  //    condition: x + 1 + last <= k

  vector<vector<ll>> dp(n + 1, vector<ll>(k)); // [0..n][0..k-1]

  // a = [last] is valid
  for (int last = 0; last <= k - 1; ++last) {
    dp[0][last] = 1;
  }

  for (int sum = 1; sum <= n; ++sum) {
    for (int last = 0; last <= k - 1; ++last) {
      ll acc = 0;
      for (int x = 0; x <= k - last - 1; ++x) {
        int delta = (x + 1) * (last + 1);
        if (sum - delta >= 0) {
          acc = addMod(acc, dp[sum - delta][x]);
        }
      }
      dp[sum][last] = acc;
    }
  }

  ll result = 0;
  for (int last = 0; last <= k - 1; ++last) {
    result = addMod(result, dp[n][last]);
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