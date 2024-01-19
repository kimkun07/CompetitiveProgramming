#include <bits/stdc++.h>

int a[2005];
int v[10'005];

void solve(int testcase) {
  int n, k, d;
  std::cin >> n >> k >> d;
  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i];
  }
  for (int i = 1; i <= k; ++i) {
    std::cin >> v[i];
  }

  // n: 2000
  // k: 10^5
  // d: 10^9

  // acc action, flush action
  int result = 0;
  // day=2n까지만 flush를 참았을 때를 확인하면 된다.
  // flush를 참은 경우 최대 n까지 획득 가능한데,
  // 한 번도 안 참은 경우에도 2n일 동안 n만큼 획득할 수 있기 때문이다.
  int finalDay = (2 * n < d) ? (2 * n) : d; // min(2 * n, d)
  for (int i = 1; i <= finalDay; ++i) {
    // day=i 일 때 처음 flush한 경우, 총점 scoreWhenFlush 획득
    int cnt = 0;
    for (int j = 1; j <= n; ++j) {
      if (a[j] == j) {
        cnt += 1;
      }
    }
    // 한 번 flush한 이후에는 어차피 한 번에 1점 이상 획득할 수 없다.
    // acc -> flush -> acc -> flush 로 1점씩 획득하기
    int scoreWhenFlush = cnt + (d - i) / 2;
    result = (scoreWhenFlush > result) ? scoreWhenFlush : result;
    
    
    // flush 하지 않은 경우, 1..b acc
    const int b = v[(i - 1) % k + 1];
    for (int j = 1; j <= b; ++j) { // b <= n
      a[j]++;
    }
  }

  std::cout << result << std::endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int T;
  std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve(t);
  }
  return 0;
}