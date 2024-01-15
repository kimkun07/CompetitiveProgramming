#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;
typedef long long ll;

void solve(int testcase) {
  int n, x;
  // n : 2*10^5, x: 10^9
  cin >> n >> x;
  vector<int> a;
  // O(n log n) : 18 * (2*10^5) = 3.6 * 10^6
  for (int i = 0; i < n; ++i) {
    int temp;
    cin >> temp;
    a.push_back(temp);
  }
  sort(a.begin(), a.end());

  ll currentX = 0;
  ll result = 1;
  // O(n)
  for (int i = 0; i < n; ++i) {
    int num = i + 1;
    ll hGain = (i == 0) ? 0 : (a[i] - a[i - 1]);
    ll gain = hGain * (num - 1);
    currentX = currentX + gain;

    if (currentX > x) {
      break;
    }

    ll idealH = a[i] + (x - currentX) / num;
    ll finalH = ((i + 1) < n) ? min(idealH, (ll)a[i + 1]) : idealH;
    result = max(finalH, result);
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