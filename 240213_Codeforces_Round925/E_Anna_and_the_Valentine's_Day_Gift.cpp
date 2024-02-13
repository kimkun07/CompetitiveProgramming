#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

void printSasha(bool yes) {
  if (yes) {
    cout << "Sasha"
         << "\n";
  } else {
    cout << "Anna"
         << "\n";
  }
}

void solve(int testcase) {
  int n, m;
  cin >> n >> m;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }

  // Anna tries to reduce the length
  // Sasha will save largest 000.

  int totalLength = 0;
  vector<int> zeros(n);
  for (int i = 1; i <= n; ++i) {
    string s = to_string(a[i]);
    totalLength += s.length();

    zeros[i - 1] = 0;
    while (true) {
      if (a[i] % 10 == 0) {
        zeros[i - 1] += 1;
        a[i] /= 10;
      } else {
        break; // a[i] != 0. always reachable
      }
    }
  }

  auto willBeTrue = [](const int &front, const int &back) -> bool {
    return front > back;
  };

  sort(zeros.begin(), zeros.end(), willBeTrue);
  for (int i = 0; i < n; ++i) {
    if (i % 2 == 0) {
      totalLength -= zeros[i];
    }
  }

  bool sashaWin = (totalLength >= (m + 1));
  printSasha(sashaWin);
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