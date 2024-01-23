#include <array>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

const int N_CONST = 1005;

using arr44 = array<array<int, 4>, 4>;
arr44 arr4 = {{
    {1, 1, 0, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
}};
arr44 arr8 = {{
    {1, 1, 1, 1},
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
}};
arr44 arr12 = {{
    {1, 1, 1, 1},
    {1, 1, 1, 1},
    {1, 1, 0, 0},
    {1, 1, 0, 0},
}};
arr44 arr16 = {{
    {1, 1, 1, 1},
    {1, 1, 1, 1},
    {1, 1, 1, 1},
    {1, 1, 1, 1},
}};
array<arr44, 4> arrs = {arr4, arr8, arr12, arr16};

arr44 arr6 = {{
    {1, 1, 0, 0},
    {1, 0, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0},
}};
arr44 arr10 = {{
    {0, 0, 1, 1},
    {0, 1, 0, 1},
    {1, 0, 0, 1},
    {1, 1, 1, 1},
}};

void printAns(bool yes) {
  if (yes) {
    cout << "Yes"
         << "\n";
  } else {
    cout << "No"
         << "\n";
  }
}
void printMatrix(vector<vector<int>> &mat) {
  const int n = mat.size();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << mat[i][j] << " ";
    }
    cout << "\n";
  }
}

void fillUpper(vector<vector<int>> &mat, arr44 &upper) {
  const int nn = 4;
  for (int i = 0; i < nn; ++i) {
    for (int j = 0; j < nn; ++j) {
      mat[i][j] = upper[i][j];
    }
  }
}

void solve(int test) {
  int n, k;
  cin >> n >> k;

  // Note: n is even
  // n: 2 ~ 1000
  // k: 0 ~ n^2

  if (k % 2 == 1) {
    printAns(false);
    return;
  }

  // n : 2 exception
  if (n == 2) {
    printAns(true);
    vector<vector<int>> matrix = (k == 2) ? vector<vector<int>>{{1, 0}, {0, 1}}
                                 : (k == 0)
                                     ? vector<vector<int>>{{0, 0}, {0, 0}}
                                     : vector<vector<int>>{{1, 1}, {1, 1}};
    printMatrix(matrix);
    return;
  }

  if ((k == 2) or (k == n * n - 2)) {
    printAns(false);
    return;
  }

  vector<vector<int>> matrix(n, vector<int>(n));

  // #region Upper
  if ((k % 4 == 0) and (k >= n * n - 12)) {
    // n * n
    // n * n - 4
    // n * n - 8
    // n * n - 12
    const int shouldFill = k - (n * n - 16);
    fillUpper(matrix, arrs[shouldFill / 4 - 1]);
    k = n * n - 16;
  }

  if (k % 4 == 2) {
    if (k <= n * n - 10) {
      k -= 6;
      // it is okay to use only 6
      fillUpper(matrix, arr6);
    } else {
      // k == n * n - 6
      k = n * n - 16;
      // should use 10
      fillUpper(matrix, arr10);
    }
  }

  // #endregion Upper

  // Now, k % 4 == 0 and k <= n * n - 16
  for (int i = 0; i < n; i += 2) {
    for (int j = 0; j < n; j += 2) {
      if (i < 4 and j < 4) {
        // Upper part
        continue;
      }
      if (k > 0) {
        matrix[i][j] = 1;
        matrix[i][j + 1] = 1;
        matrix[i + 1][j] = 1;
        matrix[i + 1][j + 1] = 1;
        k -= 4;
      } else {
        break;
      }
    }
  }

  printAns(true);
  printMatrix(matrix);
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