#include <iostream>
#include <map>
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
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  map<char, int> countMap;
  for (char c = 'a'; c <= 'z'; ++c) {
    countMap[c] = 0;
  }

  for (int i = 0; i < n; ++i) {
    for (auto &&[c, count] : countMap) {
      if (count == a[i]) {
        cout << c;
        ++count;
        break;
      }
    }
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