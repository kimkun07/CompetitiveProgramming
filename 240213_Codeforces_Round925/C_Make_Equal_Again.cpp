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

void solve(int testcase) {
  int n;
  cin >> n;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }

  int leftDiff = -1; // 1..(leftDiff-1) is same
  for (int i = 1; i <= n; ++i) {
    if (a[i] != a[1]) {
      leftDiff = i;
      break;
    }
  }

  int rightDiff; // (rightDiff+1)..n is same
  for (int i = n; i >= 1; --i) {
    if (a[i] != a[n]) {
      rightDiff = i;
      break;
    }
  }

  int result;
  if (leftDiff == -1) {
    // no change: 1..n is same
    result = 0;
  } else if (a[1] == a[n]) {
    // change leftDiff..rightDiff
    result = rightDiff - leftDiff + 1;
  } else {
    // change leftDiff..n or 1..rightDiff
    result = min(rightDiff - 1 + 1, n - leftDiff + 1);
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