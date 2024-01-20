// #238707805

#include <algorithm>
#include <cstring>
#include <ctime>
#include <iostream>
#include <random>
#include <set>
#include <vector>

using namespace std;
const int maxn = 200005;
const int mod = 998244353;
int T, n, m, p1[maxn], p2[maxn];
int lowbit(int x) { return x & -x; }
struct tl_s {
  int mx, data[maxn * 2];
  void clear(int x) {
    for (int i = 1; i <= mx; ++i)
      data[i] = 0;
    mx = x;
  }
  int add(int x) {
    for (; x <= mx; x += lowbit(x))
      data[x]++;
  }
  int ask(int x) {
    int res = 0;
    for (; x; x -= lowbit(x))
      res += data[x];
    return res;
  }
} t1;
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> T;
  while (T--) {
    int ans = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
      cin >> p1[i];
    for (int i = 1; i <= m; ++i)
      cin >> p2[i], p2[i]++;
    t1.clear(m);
    for (int i = m; i >= 1; --i) {
      ans = (ans + (long long)n * t1.ask(p2[i])) % mod;
      t1.add(p2[i]);
    }
    t1.clear(2 * n - 1);
    for (int i = n; i >= 1; --i) {
      for (int j = 0, tmp = p1[i]; j < m; ++j, tmp *= 2) {
        if (tmp > 2 * n - 1) {
          ans = (ans + (long long)(m - j) * (m - j + 1) / 2 % mod * (n - i)) %
                mod;
          break;
        }
        ans = (ans + (long long)t1.ask(tmp) * (m - j)) % mod;
      }
      for (int j = 0, tmp = p1[i]; tmp && j < m; ++j, tmp /= 2) {
        if (j)
          ans = (ans + (long long)t1.ask(tmp) * (m - j)) % mod;
      }
      t1.add(p1[i]);
    }
    cout << ans << '\n';
  }
  return 0;
}