#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;
typedef long long ll;

const int N_const = 200'005;
int p[N_const];
int q[N_const];
ll modNum = 998'244'353;

// Binary Indexed Tree
int rightmostOneBit(int num) { return (num & (-num)); }
int rightmostZeroBit(int num) { return rightmostOneBit(~num); }

void update(vector<int> &tree, int index, int plus) {
  if (not(index < tree.size())) {
    return;
  }
  tree[index] += plus;
  int nextIndex = index + rightmostZeroBit(index);
  update(tree, nextIndex, plus);
}

// sum of 0..index
ll sum(vector<int> &tree, int index) {
  if (index < 0) {
    return 0;
  }
  if (index == 0) {
    return tree[index];
  }
  // tree[index] contains elements of `num` EA
  // tree[index] = sum of (index - num + 1)..index
  int num = rightmostZeroBit(index);
  int nextIndex = index - num;
  return (tree[index] + sum(tree, nextIndex)) % modNum;
}

// sum of left..right
ll range(vector<int> &tree, int left, int right) {
  return (sum(tree, right) - sum(tree, left - 1)) % modNum;
}

void solve(int testcase) {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; ++i) {
    cin >> p[i];
  }
  for (int i = 0; i < k; ++i) {
    cin >> q[i];
  }

  // p[i]: permutation of [1, 3, 5, ... 2n - 1]
  // q[i]: permutation of [0, 1, 2, ... k - 1]

  ll result = 0;
  // a[i * k + j] = p[i] * 2^q[j]
  // find number of all inversion pair (i, j)
  // a: n row * k col

  vector<int> seg(k);
  // 1. Within one row: Find inversion of Q
  ll qInversionCount = 0;
  for (int i = 0; i < k; ++i) {
    update(seg, q[i], 1);

    // larger finds EA of j
    // q[j] is in q[i]+1..k-1 -> q[j] > q[i]
    ll larger = range(seg, q[i] + 1, k - 1);
    qInversionCount += larger;
    qInversionCount %= modNum;
  }
  result += (qInversionCount * n) % modNum;
  result %= modNum;

  // 2. Inter-row: j-th row with i-th row
  // p[j] * 2^a > p[i] * 2^b (a: 0..k-1, b: 0..k-1)
  // p[j] > p[i] * 2^(b-a)   (t = b - a: k-1..-(k-1))
  seg = vector<int>(2 * n);
  for (int i = 0; i < n; ++i) {
    // NOTE: p[j], p[i] < 4 * 10^5 < 2^19
    // t < -19 -> larger = i
    // t > 19 -> larger = 0

    // 2-1. check for -19 <= t <= k - 1
    for (int t = max(-19, -(k - 1)); t <= k - 1; ++t) {
      // p[i] * 2^t
      ll multipliedP = (t >= 0) ? (((ll)p[i]) << t) : (p[i] >> (-t));
      if (not(multipliedP + 1 <= 2 * n - 1)) {
        // t > 19 -> larger = 0
        break;
      }
      // (multipliedP == 0) is ok because all p[j] >= 1

      // find p[j] > p[i] * 2^t
      ll larger = range(seg, multipliedP + 1, 2 * n - 1);

      // number of cases for b - a = t
      // (t, 0), (t + 1, 1), (t + 2, 2), ... (t + (k-1), k-1)
      // 0 <= b <= k-1
      // t <= b <= t + (k - 1)
      // max(0, t) <= b <= min(k-1, t + (k-1))
      int cases = min(k - 1, t + (k - 1)) - max(0, t) + 1;
      cases = max(0, cases);
      // larger * cases = cases of ((j, a), (i, b))
      result += (larger * cases) % modNum;
      result %= modNum;
    }

    // 2-2. check for t < -19
    ll larger = i;
    // number of cases for b - a <= -20
    // = 1 + 2 + ... h
    int h = (-20) - (-(k - 1)) + 1;
    if (not(h <= 0)) {
      ll outercases = ((ll)h) * (h + 1) / 2;

      result += (larger * outercases) % modNum;
      result %= modNum;
    }

    update(seg, p[i], 1);
  }

  std::cout << result << "\n";
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