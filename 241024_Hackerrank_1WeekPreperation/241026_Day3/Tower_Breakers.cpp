#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'towerBreakers' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER m
 */

int towerBreakers(int n, int m) {
  // Factorize m = a_1^{x_1} a_2^{x_2} ... a_l^{x_l}
  // k = x_1 + x_2 + ... + x_l

  // Game can be viewed as (k, k, ..., k)
  // Each player can subtract any value to one of the tower
  // Player wins if it makes (0, 0, ..., 0)

  if (m == 1) {
    // Cannot move at all (k=0)
    return 2;
  }

  // n:1 (a)    => P1 wins (for all value a > 0)
  // n:2 (a, a) => P2 can make (1, 1), then P1 should break to n:1, P2 wins
  //               if P1 subtracts b, P2 does same to other tower
  // n:3 (a, a, a) => P1 can break to n:2, P1 wins
  // n:4           => P2 can move symmetrically to make (b, b, c, c)
  return (n % 2 == 1) ? 1 : 2;
}

int main() {
  ofstream fout(getenv("OUTPUT_PATH"));

  string t_temp;
  getline(cin, t_temp);

  int t = stoi(ltrim(rtrim(t_temp)));

  for (int t_itr = 0; t_itr < t; t_itr++) {
    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input =
        split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    int result = towerBreakers(n, m);

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

vector<string> split(const string &str) {
  vector<string> tokens;

  string::size_type start = 0;
  string::size_type end = 0;

  while ((end = str.find(" ", start)) != string::npos) {
    tokens.push_back(str.substr(start, end - start));

    start = end + 1;
  }

  tokens.push_back(str.substr(start));

  return tokens;
}
