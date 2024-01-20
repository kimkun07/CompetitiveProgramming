// #238733768

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

int T;
ll n, k;
ll p[200002];
ll q[200002];
ll seg[1600002];
int mod = 998244353;
int mx;
void Add(int idx) {
  idx++;
  while (idx <= mx) {
    seg[idx] += 1;
    idx += (idx & -idx);
  }
}
ll sum(int idx) {
  idx++;
  ll ret = 0;
  while (idx > 0) {
    ret += seg[idx];
    idx -= (idx & -idx);
  }
  return ret;
}
int Query(int node, int nL, int nR, int l, int r) {
  return sum(r) - sum(l - 1);
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  while (T--) {
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
      cin >> p[i];
    for (int i = 1; i <= k; i++)
      cin >> q[i];
    mx = 2 * max(2 * n, k);
    for (int i = 0; i < mx; i++)
      seg[i] = 0;
    ll qinv = 0;
    for (int i = 1; i <= k; i++) {
      Add(q[i]);
      qinv = (qinv + Query(1, 0, k - 1, q[i] + 1, k - 1)); // (q[i]+1)..(k-1)
    }
    qinv %= mod;
    ll ans = qinv * n;
    
    ans %= mod;
    for (int i = 0; i < mx; i++)
      seg[i] = 0;
    ll pinv = 0;
    for (int i = 1; i <= n; i++) {
      Add(p[i]);
      pinv = (pinv + Query(1, 0, 2 * n - 1, p[i] + 1, 2 * n - 1));
    }
    pinv %= mod;
    ans = (ans + pinv * k) % mod;
    for (int x = 1; x < k; x++) {
      ll cnt = k - x;
      if (x >= 19) {
        break;
      }
      for (int i = 0; i < mx; i++)
        seg[i] = 0;
      for (int i = 1; i <= n; i++) {
        if ((ll)(1LL << x) * p[i] > 2 * n) {
          Add(p[i]);
          continue;
        }
        ans =
            (ans + cnt * Query(1, 0, 2 * n - 1, (1LL << x) * p[i], 2 * n - 1)) %
            mod;
        Add(p[i]);
      }
    }
    int xx = (n * (n - 1) / 2) % mod;
    for (int x = 1; x < k; x++) {
      ll cnt = k - x;
      if (x >= 19) {
        ans = (ans + cnt * xx) % mod;
        continue;
      }
      for (int i = 0; i < mx; i++)
        seg[i] = 0;
      ll p2 = (1 << x);
      for (int i = 1; i <= n; i++) {
        ans = (ans + cnt * Query(1, 0, 2 * n - 1, p[i] / p2 + 1, 2 * n - 1)) %
              mod;
        Add(p[i]);
      }
    }
    cout << ans << '\n';
  }
  return 0;
}