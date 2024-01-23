#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;
typedef long long ll;

void solve(int testcase) {
  int n, k;
  cin >> n >> k;
  vector<int> a;

  for (int i = 0; i < n; ++i) {
    int temp;
    cin >> temp;
    a.push_back(temp);
  }

  // Divide into ranges
  vector<vector<int>> groups;
  int prev;
  cin >> prev; // h[0]
  groups.push_back(vector<int>());
  groups.back().push_back(a[0]);
  for (int i = 1; i < n; ++i) {
    int temp;
    cin >> temp;
    if (prev % temp == 0) {
      groups.back().push_back(a[i]);
    } else {
      groups.push_back(vector<int>());
      groups.back().push_back(a[i]);
    }
    prev = temp;
  }

  // sum of subarray (when non-negative)
  int max_len = 0;
  for (auto &&group : groups) {
    ll curr_sum = 0;
    // sum of group[start, end]
    int start = 0;
    for (int end = 0; end < group.size(); ++end) {
      curr_sum += group[end];
      while (curr_sum > k) {
        curr_sum -= group[start];
        start += 1;
      }
      max_len = max(max_len, end - start + 1);
    }
  }

  cout << max_len << "\n";
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