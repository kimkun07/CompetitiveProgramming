#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;
typedef long long ll;

void solve(int test) {
  int n;
  cin >> n;
  string s;
  cin >> s;

  set<string> currentSet;
  set<string> nextSet;
  currentSet.insert(s);
  
  ll result = 0;
  // Use references to avoid copying
  set<string> &currentSetRef = currentSet;
  set<string> &nextSetRef = nextSet;
  
  for (int length = n; length >= 1; length--) {
    // currentSet element: string with `length`
    // nextSet element: string with `length - 1`
    for (auto &&p : currentSetRef) {
      string str = p;

      if (str.length() > 0) {
        string dropFirst = str.substr(1, str.length());
        nextSetRef.insert(dropFirst);
      }
      if (str.length() > 1) {
        string dropSecond = str[0] + str.substr(2, str.length());
        nextSetRef.insert(dropSecond);
      }
    }

    result += nextSetRef.size();
    // currentSet = nextSet. No need to copy all set.
    swap(currentSetRef, nextSetRef);
    nextSetRef.clear();
  }

  cout << result << endl;
}

int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve(t);
  }
  return 0;
}