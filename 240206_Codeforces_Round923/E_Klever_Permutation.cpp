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
  int n, k;
  cin >> n >> k;

  vector<int> result(n + 1); // 1..n

  // Reason
  // Sliding Window: abs(a[i] - a[i + k]) should be 1
  // If a[1 + k] == a[1] + 1, then a[2 + k] should be a[2] - 1

  int startNum = 1;
  int delta = 1;
  for (int startI = 1; startI <= k; ++startI) {
    int cnt = (n - startI + 1 + (k - 1)) / k; // ceil(n - startI + 1)
    int num = (delta == 1) ? startNum : (startNum + cnt - 1);
    // result will be filled with startNum .. startNum + cnt - 1
    for (int i = startI; i <= n; i += k) {
      result[i] = num;
      num += delta;
    }
    delta = delta * -1;
    startNum += cnt;
  }

  for (int i = 1; i <= n; ++i) {
    cout << result[i] << " ";
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