#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;
typedef long long ll;

int a[2005];
int v[10'005];

void solve(int testcase) {
  int n, k, d;
  cin >> n >> k >> d;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= k; ++i) {
    cin >> v[i];
  }

  // n: 2000
  // k: 10^5
  // d: 10^9

  // acc action, flush action
  int result = 0;
  // a[i] gets score when cnt(b[j] >= i) == i
  // a[i] <= n -> b[i]도 n번만 확인하면 된다.
  for (int i = 1; i <= min(n + 1, d); ++i) {
    // 1) i-th day: very first flush
    // 최초의 경우: 잘하면 고득점할 수 있다.
    int cnt = 0;
    for (int j = 1; j <= n; ++j) {
      if (a[j] == j) {
        cnt += 1;
      }
    }

    // 나머지 경우: 어차피 한 번에 1점 이상 획득할 수 없다.
    // acc -> flush -> acc -> flush 로 1점씩 획득하기
    int t = cnt + (d - i) / 2;
    result = max(t, result);

    // 2) Assume acc action on i-th day
    const int b = v[(i - 1) % k + 1];
    for (int j = 1; j <= b; ++j) { // b <= n
      a[j]++;
    }
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