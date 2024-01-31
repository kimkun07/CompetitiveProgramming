#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

int a[200'005];

int gcd(int a, int b) {
  // a could be 0
  if (b == 0) {
    return a;
  }
  return gcd(b, a % b);
}

// divisor including 1, excluding n
vector<int> get_divisor(int n) {
  vector<int> result;

  for (int i = 1; i < n; ++i) {
    if (n % i == 0) {
      result.push_back(i);
    }
  }

  // Compiler may use NVRO
  return result;
}

void solve(int testcase) {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  // Solve
  // 1. Get divisor list of n (except n)
  //    divisor.size() < 20
  // 2. For each division of subarray, find m = gcd(diff)
  //    ex) if l = 2
  //    First element
  //    a1 - a3 = _ * m + c1
  //    a3 - a5 = _ * m + c1
  //    Second element
  //    a2 - a4 = _ * m + c2
  //    a4 - a6 = _ * m = c2
  //    possible iff m is equal to or greater than 2

  // if NVRO is used, divisor will just refer to same object as result
  // if NVRO is not used, move constructor will be used from result to divisor
  vector<int> divisor = get_divisor(n);

  int ans = 1; // when l == n
  for (auto &&l : divisor) {
    // divide a[n] into into subarr[row][col]
    // subarr has length of l
    // l != n
    int subarrEa = n / l;
    int m = a[0] - a[1 * l + 0];
    // m could be 0. gcd(a, 0) = gcd(0, a) = a
    for (int col = 0; col < l; ++col) {
      for (int row = 1; row < subarrEa; ++row) {
        int diff = abs(a[col] - a[row * l + col]);
        m = gcd(m, diff);
      }
    }
    if (m >= 2 or m == 0) {
      ans += 1;
    }
  }

  cout << ans << "\n";
  // cout << "[TEST OUT] " << ans << endl;
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