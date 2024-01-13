#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;
typedef long long ll;

int a[200'005];

void divisor(int n) {
  
}

void solve(int testcase) {
  int n; cin >> n;
  for(int i = 0; i < n; ++i){
    cin >> a[i];
  }
  cout << "Case " + to_string(testcase) + ": " << "\n";
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