#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'gridChallenge' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING_ARRAY grid as parameter.
 */

string gridChallenge(vector<string> grid) {
  int n = grid.size();
  vector<vector<char>> new_grid(n);

  for (int i = 0; i < n; i++) {
    new_grid[i] = vector<char>(grid[i].begin(), grid[i].end());
    sort(new_grid[i].begin(), new_grid[i].end());
  }

  for (int c = 0; c < n; c++) {
    int r;
    for (r = 0; r < n - 1; r++) {
      if (new_grid[r][c] <= new_grid[r + 1][c]) {
        // sorted
        continue;
      } else {
        break;
      }
    }
    if (r != n - 1) {
      return "NO";
    }
  }
  return "YES";
}

int main() {
  ofstream fout(getenv("OUTPUT_PATH"));

  string t_temp;
  getline(cin, t_temp);

  int t = stoi(ltrim(rtrim(t_temp)));

  for (int t_itr = 0; t_itr < t; t_itr++) {
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
      string grid_item;
      getline(cin, grid_item);

      grid[i] = grid_item;
    }

    string result = gridChallenge(grid);

    fout << result << "\n";
  }

  fout.close();

  return 0;
}

string ltrim(const string &str) {
  string s(str);

  s.erase(s.begin(),
          find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));

  return s;
}

string rtrim(const string &str) {
  string s(str);

  s.erase(
      find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
      s.end());

  return s;
}
