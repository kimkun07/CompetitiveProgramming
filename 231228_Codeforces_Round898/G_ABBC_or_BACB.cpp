#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;
typedef long long ll;

void solve(int testcase) {
  string s;
  cin >> s;

  // Sum of BA...AB Sequence
  // ..ABA...    -> either way
  // BA...ABA... -> can do both
  // ...ABBA...  -> can do both
  // ...AA.....  -> 0

  bool bb = false;
  for (int i = 0; i < s.size() - 1; ++i) {
    if (s[i] == 'B' and s[i + 1] == 'B') {
      bb = true;
    }
  }

  bool b = false;
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == 'B') {
      b = true;
    }
  }

  bool cont = false;
  vector<int> a;
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == 'A') {
      if (cont) {
        a.back() += 1;
      } else {
        a.push_back(1);
        cont = true;
      }
    } else {
      cont = false;
    }
  }
  
  ll sum = 0;
  int minA = INT_MAX;
  for (auto &&i : a) {
    sum += i;
    minA = min(minA, i);
  }

  ll result = 0;
  if (bb or (s.front() == 'B' or s.back() == 'B')) {
    result = sum;
  } else if (b) {
    // ...B...B...
    // There should be one part missing
    result = sum - minA;
  } else {
    result = 0;
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