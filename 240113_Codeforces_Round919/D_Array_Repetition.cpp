#include <iostream>
#include <map>
#include <ranges>
#include <set>
#include <vector>


using namespace std;
typedef long long ll;

int mySearch(std::ranges::drop_view<
                 std::ranges::ref_view<std::vector<std::tuple<bool, ll, int>>>>
                 op,
             ll k) {
  auto t = op.back();
  bool isAppend;
  ll afterLen;
  int x;
  tie(isAppend, afterLen, x) = t;

  if (isAppend) {
    if (k == afterLen) {
      // Found
      return x;
    } else if (k < afterLen) {
      return mySearch(op | ranges::views::drop(1), k);
    }
  } else {
    return mySearch(op | ranges::views::drop(1), k % x);
  }
  return -1;
}

void solve(int testcase) {
  int n, q;
  cin >> n >> q;
  vector<tuple<bool, ll, int>> op; // isAppend, length after op, argument x
  ll len = 0;
  for (int i = 0; i < n; ++i) {
    int b, x;
    cin >> b >> x;
    switch (b) {
    case 1:
      len += 1;
      op.push_back(make_tuple(true, len, x));
      break;
    default:
      len *= x;
      op.push_back(make_tuple(false, len, x));
      break;
    }
  }
  for (int i = 0; i < q; ++i) {
    ll k;
    cin >> k;
    cout << mySearch(ranges::views::all(op), k) << " ";
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