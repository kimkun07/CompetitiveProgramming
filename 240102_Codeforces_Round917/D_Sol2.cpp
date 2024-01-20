// #238694785

#include <bits/stdc++.h>
#pragma GCC optimize("Ofast,no-stack-protector,fast-math", 3)
// using LL=__int128_t;
#define cln cerr << "Line:   " << __LINE__ << "    "
#define pct __builtin_popcountll
#define ctz __builtin_ctzll
#define mkp make_pair
#define all(x) x.begin(), x.end()
using namespace std;
const int N = (1 << 21) + 10, _g = 3, M = 998244353, M1 = 1e9 + 7, M2 = 1e9 + 9;
using ll = long long;
#define pli pair<ll, int>
using ul = unsigned long long;
using ld = double;
mt19937_64 rg(random_device{}());
const ll INF = 3e18;
template <typename tp1, typename tp2> void ckmx(tp1 &x, const tp2 &y) {
  x < y ? x = y : 0;
}
template <typename tp1, typename tp2> void ckmn(tp1 &x, const tp2 &y) {
  x > y ? x = y : 0;
}
void add(int &x, int y) { (x += y) >= M ? x -= M : 0; }
void del(int &x, int y) { (x -= y) < 0 ? x += M : 0; }
void add(int &x, ul y, int z) { x = (y * z + x) % M; }
namespace MATH {
vector<int> jc, nv;
int dv2(int x) { return x & 1 ? x + M >> 1 : x >> 1; }
int C(int n, int m) { return 1ll * jc[n] * nv[m] % M * nv[n - m] % M; }
int P(int n, int m) { return 1ll * jc[n] * nv[n - m] % M; }
int D(int n, int m) {
  if (n < 0 || m < 0)
    return 0;
  if (!n)
    return 1;
  if (!m)
    return 0;
  return C(n + m - 1, m - 1);
}
constexpr int qp(ll a, ll x = M - 2) {
  int res = 1;
  for (; x; x >>= 1, a = a * a % M)
    (x & 1) && (res = a * res % M);
  return res;
}
void init(int n) {
  int x;
  jc.resize(n + 2), nv.resize(n + 2);
  jc[0] = nv[0] = jc[1] = nv[1] = 1;
  for (x = 2; x <= n; ++x) {
    jc[x] = 1ll * x * jc[x - 1] % M;
    nv[x] = ll(M - M / x) * nv[M % x] % M;
  }
  for (x = 1; x <= n; ++x)
    nv[x] = 1ll * nv[x - 1] * nv[x] % M;
}
} // namespace MATH
using namespace MATH;
int T, n, m, a[N], b[N], ct[N];
ll ans;
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int i, j, k, l, r, md, x, y, z, k2;
  for (cin >> T; T--;) {
    cin >> n >> m, ans = 0;
    for (x = 1; x <= n; ++x)
      cin >> a[x];
    for (x = 1; x <= m; ++x)
      cin >> b[x], ++b[x], ct[x] = 0;
    for (x = m; x; --x) {
      for (k = b[x]; k; k -= k & -k)
        ans += ct[k];
      for (k = b[x]; k <= m; k += k & -k)
        ++ct[k];
    }
    ans = ans * n % M;
    for (x = 1; x <= n + n - 1; ++x)
      ct[x] = 0;
    for (x = n; x; --x) {
      for (i = 0; (a[x] >> i) && i < m; ++i) {
        for (k = a[x] >> i, z = 0; k; k -= k & -k)
          z += ct[k];
        ans += 1ll * z * (m - i);
      }
      for (i = 1; (a[x] << i) < n + n && i < m; ++i) {
        for (k = a[x] << i, z = 0; k; k -= k & -k)
          z += ct[k];
        ans += 1ll * z * (m - i);
      }
      ans += 1ll * (m - i) * (m - i + 1) / 2 % M * (n - x) % M;
      ans %= M;
      for (k = a[x]; k <= n + n - 1; k += k & -k)
        ++ct[k];
    }
    printf("%lld\n", ans % M);
  }
  return 0;
}