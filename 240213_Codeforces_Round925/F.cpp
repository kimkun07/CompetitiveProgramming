#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

void printAns(bool yes) {
  if (yes) {
    cout << "Yes"
         << "\n";
  } else {
    cout << "No"
         << "\n";
  }
}

void solve(int testcase) {
  int n, k;
  cin >> n >> k;

  vector<int> correct(n - 1);
  bool wrong = false;

  int theFirst;
  {
    // i = 0
    cin >> theFirst;
    for (int j = 0; j < n - 1; ++j) {
      cin >> correct[j];
    }
  }

  if (k == 1) {
    printAns(not wrong);
    return;
  }

  // theFirst is not positioned yet
  int candidate = -1;
  {
    // i = 1
    int first;
    cin >> first;
    vector<int> me(n - 1);
    for (int j = 0; j < n - 1; ++j) {
      cin >> me[j];
    }

    int p = 0;
    for (int j = 0; j < n - 1; ++j) {
      bool firstFlag = false;
      if (correct[p] == first) {
        ++p;
        firstFlag = true;
      }

      if (me[j] == correct[p]) {
        ++p;
      } else if (me[j] == theFirst) {
        if (not firstFlag) {
          // Case 1
          // p-1    p         p+1
          // me[j]  theFirst  me[j+1]
          correct.insert(correct.begin() + p, theFirst);
          ++p;
          theFirst = 0;
        } else {
          // Case 2
          // p-2    p-1    p         p+1
          // me[j]  first  theFirst  me[j+1]
          // Can be in p or p-1 (No information about first - theFirst)
          candidate = p - 1; // candidate or candidate + 1
        }
      } else {
        wrong = true;
      }
    }
  }

  if (k == 2) {
    printAns(not wrong);
    return;
  }

  {
    // i = 2
    int first;
    cin >> first;
    vector<int> me(n - 1);
    for (int j = 0; j < n - 1; ++j) {
      cin >> me[j];
    }

    int p = 0;
    for (int j = 0; j < n - 1; ++j) {
      bool firstFlag = false;
      if (correct[p] == first) {
        ++p;
        firstFlag = true;
      }

      if (me[j] == correct[p]) {
        ++p;
      } else if (me[j] == theFirst) {
        if (not firstFlag) {
          // Case 1
          // p-1    p         p+1
          // me[j]  theFirst  me[j+1]
          if (not(candidate == p or candidate + 1 == p)) {
            wrong = true;
          }
          correct.insert(correct.begin() + p, theFirst);
          ++p;
        } else {
          // Case 2
          // p-2    p-1    p         p+1
          // me[j]  first  theFirst  me[j+1]
          // Can be in p or p-1 (No information about first - theFirst)
          if (candidate == p) {
            correct.insert(correct.begin() + p, theFirst);
            ++p;
          } else if (candidate == p - 2) {
            correct.insert(correct.begin() + (p - 1), theFirst);
            ++p;
          } else {
            wrong = true;
          }
        }
      } else {
        wrong = true;
      }
    }
  }

  for (int i = 3; i < k; ++i) {
    int first;
    cin >> first;
    vector<int> me(n - 1);
    for (int j = 0; j < n - 1; ++j) {
      cin >> me[j];
    }

    int p = 0;
    for (int j = 0; j < n - 1; ++j) {
      if (correct[p] == first) {
        ++p;
      }

      if (me[j] == correct[p]) {
        ++p;
      } else {
        wrong = true;
      }
    }
  }

  printAns(not wrong);
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