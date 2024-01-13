#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;
typedef long long ll;

void solve(int testcase) {
  int n, k, x;
  cin >> n >> k >> x;
  vector<int> a;
  for (int i = 0; i < n; ++i) {
    int temp;
    cin >> temp;
    a.push_back(temp);
  }
  sort(a.begin(), a.end(), [](int &a, int &b) -> bool { return a > b; });

  ll sum = 0;
  for(int i = 0; i < n; ++i){
    sum += (i < x) ? (-a[i]) : a[i];
  }

  ll acc = 0;
  ll maxGain = 0;
  for (int i = 0; i < k; ++i) {
    // +a[i], - 2 * a[i + x]
    acc += a[i] - 2 * ((i + x < n) ? a[i + x] : 0);
    maxGain = max(maxGain, acc);
  }
  cout << sum + maxGain << "\n";
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