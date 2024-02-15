#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

ll modNum = 998'244'353;

int add_mod(ll a, ll b) { return ((a % modNum) + (b % modNum)) % modNum; }
int mul_mod(ll a, ll b) { return ((a % modNum) * (b % modNum)) % modNum; }

int pow_mod(ll a, ll b) {
  if (b == 0) {
    return 1;
  }
  int r = pow_mod(a, b / 2);
  return mul_mod(mul_mod(r, r), (b % 2 == 1) ? (a % modNum) : 1);
}
int inv_mod(ll x) { return pow_mod(x % modNum, modNum - 2); }
int div_mod(ll a, ll b) { return mul_mod(a, inv_mod(b)); }

const int factMax = 2000'005;
int fact_mod[factMax + 1];
// n! / k!(n - k)!
int combination(int n, int k) {
  int top = fact_mod[n];
  int bottom = mul_mod(fact_mod[k], fact_mod[n - k]);
  return div_mod(top, bottom);
}

// Case of putting n items in k boxes
ll weak_composition(int n, int k) {
  if (k <= 0) {
    throw std::runtime_error("k should be >= 1. k: " + to_string(k));
  }
  // stars and bars
  // => (n + (k-1))C(k-1)
  return combination(n + (k - 1), k - 1);
}

void solve(int testcase) {
  int c1, c2, c3, c4;
  cin >> c1 >> c2 >> c3 >> c4;

  // Solve
  // Decide 1 and 2 first.
  // Fill in 3 and 4 between 1 and 2.

  int result = 0;
  if (c1 == 0 and c2 == 0) {
    // TODO: Is there an input where all is 0?
    result = (c3 == 0 or c4 == 0) ? 1 : 0;
  } else if (c1 == 0 or c2 == 0) {
    if (c1 == 1 or c2 == 1) {
      // Sequence: ... 3, 3, 2, 4, 4, ...
      result = 1;
    } else {
      result = 0;
    }
  } else {
    if (abs(c1 - c2) > 1) {
      result = 0;
    } else {
      if (c1 == c2) {
        //  1 2 1 2
        // 4 3 4 3 4
        int cnt = c1;
        result =
            mul_mod(weak_composition(c3, cnt), weak_composition(c4, cnt + 1));
        //  2 1 2 1
        // 3 4 3 4 3
        result = add_mod(result, mul_mod(weak_composition(c4, cnt),
                                         weak_composition(c3, cnt + 1)));
      } else {
        // if c2 == c1 + 1
        //  2 1 2
        // 3 4 3 4
        // if c1 == c2 + 1
        //  1 2 1
        // 4 3 4 3
        int cnt = max(c1, c2);
        // Put 3 in `cnt` boxes, Put 4 in `cnt` boxes
        result = mul_mod(weak_composition(c3, cnt), weak_composition(c4, cnt));
      }
    }
  }

  cout << result << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  fact_mod[0] = 1;
  for (int i = 1; i <= factMax; ++i) {
    fact_mod[i] = mul_mod(fact_mod[i - 1], i);
  }

  int T;
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve(t);
  }
  return 0;
}