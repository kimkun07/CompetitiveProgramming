#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;
typedef long long ll;

void solve(int test) {
  int n;
  cin >> n;
  string s;
  cin >> s;

  ll result = 0;

  for (int length = n; length >= 1; length--) {
    // 0 ~ ((n - 1) - (length - 1)): Only one char can be saved
    // ((n - 1) - (length - 2)) ~ (n - 1): suffix of `length - 1`
    // string with `length`: char x + suffix
    set<char> charSet;
    for (auto &&i : s.substr(0, (n - 1) - (length - 1) + 1)) {
      charSet.insert(i);
    }

    result += charSet.size();
  }

  cout << result << endl;
}

int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve(t);
  }
  return 0;
}