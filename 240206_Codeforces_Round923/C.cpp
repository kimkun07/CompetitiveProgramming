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

int a[200'005], b[200'005], arr[400'005];
void solve(int testcase) {
  int n, m, k;
  cin >> n >> m >> k;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; ++i) {
    cin >> b[i];
  }

  for (int i = 1; i <= k; ++i) {
    arr[i] = 0;
  }
  for (int i = 1; i <= n; ++i) {
    arr[a[i]] = 2;
  }
  for (int i = 1; i <= m; ++i) {
    arr[b[i]] = arr[b[i]] | 1;
  }

  int aOnly = 0, bOnly = 0;
  int neither = 0;
  for (int i = 1; i <= k; ++i) {
    switch (arr[i]) {
    case 3:
      break;
    case 2:
      ++aOnly;
      break;
    case 1:
      ++bOnly;
      break;
    case 0:
      ++neither;
      break;
    default:
      throw std::runtime_error("arr value ERROR " + to_string(arr[i]));
      break;
    }
  }

  if (neither == 0 and aOnly <= k / 2 and bOnly <= k / 2) {
    printAns(true);
  } else {
    printAns(false);
  }
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