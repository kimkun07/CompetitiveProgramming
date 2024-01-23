#include <functional>
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
  int n, d;
  cin >> n >> d;
  vector<int> l(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> l[i];
  }

  // Solve
  // 1. knapsack -> find diameter of d using l[1..n]
  // 2. put leftover nodes between diameter
  //    we should check this doesn't increase diameter
  //
  // 2-A. if mx is included, leftover will not increase diameter
  //      -> simple knapsack
  // 2-B. if mx is not included, we should check every possible (left, right)
  //      left + right will be diameter
  //      new item[i] can either be put in left or right
  //      -> knapsack with two states (left, right)

  // Works well excluding l[0]
  sort(l.begin() + 1, l.end());
  if (l[n] + l[n - 1] > d) {
    // always bigger than diameter
    printAns(false);
    return;
  }

  int mx = l.back();
  {
    // Knapsack with mx included
    vector<vector<bool>> dp(n + 1, vector<bool>(d + 1));
    for (int i = 0; i <= n; ++i) {
      dp[i][0] = true;
    }

    for (int i = 1; i <= n - 1; ++i) {
      int weight = l[i];
      for (int j = 1; j <= d - mx; ++j) {
        dp[i][j] = dp[i - 1][j];
        if (j - weight >= 0) {
          dp[i][j] = dp[i - 1][j - weight] or dp[i][j];
        }
      }
    }

    if (dp[n - 1][d - mx] and d - mx > 0) {
      // Construct tree with l[1..n-1] + mx
      // Exclude if we only used l[n] because we can't handle leftover
      // Then mx >= leftover and there is always node between diameter
      printAns(true);
      return;
    }
  }

  vector<vector<bool>> dpA(d + 1, vector<bool>(d + 1));
  vector<vector<bool>> dpB(d + 1, vector<bool>(d + 1));

  auto prevDp = ref(dpA), dp = ref(dpB);
  // Knapsack with two states
  // for item l[i], we can put item left or right
  // dp(left, right) = dp(left - l, right) | dp(left, right - l) | dp(left,
  // right)
  prevDp.get()[0][0] = dp.get()[0][0] = true;
  for (int i = 1; i <= n; ++i) {
    int weight = l[i];

    swap(prevDp, dp);
    for (int left = 0; left <= d; ++left) {
      for (int right = 0; right <= d; ++right) {
        // ex: (30 + 10, 20)
        dp.get()[left][right] = prevDp.get()[left][right];
        if (left - weight >= 0) {
          dp.get()[left][right] =
              prevDp.get()[left - weight][right] or dp.get()[left][right];
        }
        if (right - weight >= 0) {
          dp.get()[left][right] =
              prevDp.get()[left][right - weight] or dp.get()[left][right];
        }
      }
    }
  }

  // Check if mx doesn't increase diameter
  for (int left = 1; left <= d; ++left) {
    int right = d - left;
    if (dp.get()[left][right]) {
      if (left >= mx and right >= mx) {
        printAns(true);
        return;
      }
    }
  }

  printAns(false);
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