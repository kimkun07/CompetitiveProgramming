#include <array>
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

// dp: [1.N][1..W], v: [1..N], w: [1..N]
void knapsack(int N, int W, vector<vector<int>> &dp, const vector<int> &v,
              const vector<int> &w) {
  for (int i = 1; i <= N; ++i) {
    int value = v[i];
    int weight = w[i];
    for (int j = 1; j <= W; ++j) {
      if (j - weight == 0 or (j - weight >= 0 and dp[i - 1][j - weight] > 0)) {
        // previous should be valid choice
        dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight] + value);
      } else {
        // previous was not valid choice
        // Cannot take
        dp[i][j] = dp[i - 1][j];
      }
    }
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
  // 1. knapsack -> find diameter of d
  // 2. we can put leftover nodes in half position of diameter.
  // 3. Check 2 doesn't increase diameter of the tree -> second knapsack
  // [Second Knapsack]
  // split diameter into half (knapsack)
  // consider two length as a and b
  // diameter doesn't increase iff a >= leftover, b >= leftover
  // we have to check split diameter so that a >= max(leftover) b >= leftover
  // [First Knapsack]
  // If there are several valid knapsack cases,
  // it is okay to greedily take largest l possible
  // Let's suppose taking largest element `ml` leads to wrong answer.
  // This means second larges element `ml2` doesn't match condition 3.
  // Split a = ml, b = d - ml, then a >= ml2 but b < ml2
  // b = d - ml < ml2, ml + ml2 > d
  // =>  ml > d / 2  (Because ml >= ml2)
  // If we had not take ml, ml cannot match condition 3 after all.

  // TODO: if n2 == 1

  // 0. Sort descending, so that big number is taken if possible in knapsack
  auto lama = [](const int &front, const int &back) -> bool {
    return front > back;
  };
  // works well excluding l[0]
  sort(l.begin() + 1, l.end(), lama);

  // 1. knapsack
  vector<vector<int>> dp(n + 1, vector<int>(d + 1));
  knapsack(n, d, dp, l, l);

  if (dp[n][d] == 0) {
    printAns(false);
    return;
  }

  // 2. backtrack for find diameter(taken) or leftover(not taken)
  vector<int> diameter;
  int notTakenMax = 0;
  int weight = d;
  for (int i = n; i >= 1; i--) {
    if (weight == 0) {
      break;
    }
    if (dp[i][weight] == dp[i - 1][weight]) {
      notTakenMax = max(l[i], notTakenMax);
    } else {
      // taken
      diameter.push_back(l[i]);
      weight -= l[i];
    }
  }

  // 3. second knapsack
  // a, b = splitIntoTwoGroup(diameter)
  // b = d - a
  // a, b both should be >= notTakenMax
  // notTakenMax <= a <= d - notTakenMax
  int lower = notTakenMax;
  int upper = d - notTakenMax;
  // split diameter into lower <= a <= upper -> knapsack
  int n2 = diameter.size();
  int d2 = upper;
  vector<vector<int>> dp2(n2 + 1, vector<int>(d2 + 1));
  
  diameter.insert(diameter.begin(), 0); // so that diameter: 1..n2
  knapsack(n2, d2, dp2, diameter, diameter);

  for (int a = lower; a <= upper; ++a) {
    if (dp2[n2][a] != 0) {
      printAns(true);
      return;
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