#include <cassert>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;
using ull = unsigned long long;

struct Info {
  bool isAppend; // op isAppend
  ull length;     // length after op
  int x;         // argument x
};

const ull kMax = 1000'000'000'000'000'000uLL;
// binary predicate which returns ​true if the first argument is less than
// (i.e. is ordered before) the second.
const auto lama = [](const Info &e, const ull &k) -> bool {
  return e.length < k;
};

int mySearch(vector<Info> &op, const vector<Info>::iterator end, ull k) {
  const auto it = lower_bound(op.begin(), end, k, lama);
  // it - 1 < k <= it

  const Info &t = *it;

  if (t.isAppend) {
    if (t.length == k) {
      return t.x;
    } else {
      throw "k: " + to_string(k) + ". t.length: " + to_string(t.length);
      // assert(t.length == k);
      // because prevLen == t.length - 1
      // and it - 1 < k <= it
    }
  } else {
    // ull prevLen = t.length / (t.x + 1);
    // Wrong: if t.length == kMax (overflow), this is incorrect

    // it is safe to dereference (it - 1)
    // b == 2 operation -> should have b == 1 opertion before
    ull prevLen = (*(it - 1)).length;
    return mySearch(op, it, (k - 1) % prevLen + 1);
  }
}

void solve(int testcase) {
  int n, q;
  cin >> n >> q;
  vector<Info> op(n);

  ull len = 0;
  for (int i = 0; i < n; ++i) {
    int b, x;
    cin >> b >> x;
    switch (b) {
    case 1: {
      len += 1;
      len = min(len, kMax);

      op[i] = {true, len, x};
      break;
    }
    default: {
      {
        ull a = len;
        ull b = (x + 1);
        len = a * b;
        if (len / b != a) {
          // detect multiplication overflow
          len = kMax;
        }
      }
      len = min(len, kMax);

      op[i] = {false, len, x};
      break;
    }
    }
  }

  for (int i = 0; i < q; ++i) {
    ull k;
    cin >> k;
    cout << mySearch(op, op.end(), k) << " ";
  }
  cout << "\n";
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