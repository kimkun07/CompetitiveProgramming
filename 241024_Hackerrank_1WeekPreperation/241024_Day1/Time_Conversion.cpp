#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'timeConversion' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string timeConversion(string s) {
  // hh:mm:ssAM or hh:mm:ssPM
  string hh = s.substr(0, 2);
  string mm = s.substr(3, 2);
  string ss = s.substr(6, 2);
  bool is_pm = (s[8] == 'P');

  int h = stoi(hh);
  if (h == 12) {
    h = 0; // 12:00:00AM -> 00:00:00, 12:00:00PM -> 12:00:00
  }
  if (is_pm) {
    h = h + 12;
  }

  char c[3];
  sprintf(c, "%02d", h);

  string ans = string(c) + ":" + mm + ":" + ss;
  return ans;
}

int main() {
  ofstream fout(getenv("OUTPUT_PATH"));

  string s;
  getline(cin, s);

  string result = timeConversion(s);

  fout << result << "\n";

  fout.close();

  return 0;
}
