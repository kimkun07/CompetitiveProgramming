#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'palindromeIndex' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

/*
 * Complete the 'palindromeIndex' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */
int palindromeIndex(string s) {
  int i = 0, j = s.size() - 1;
  int errorI = -1, errorJ;
  while (i <= j) {
    if (s[i] == s[j]) {
      i++;
      j--;
      continue;
    } else {
      // Either i or j should be removed
      errorI = i;
      errorJ = j;
      break;
    }
  }

  if (errorI == -1) {
    return -1; // Already palindrome
  }

  // Test ErrorI
  bool error = false;
  i = 0;
  j = s.size() - 1;
  while (i <= j) {
    if (i == errorI) {
      i++;
      continue;
    }
    if (s[i] == s[j]) {
      i++;
      j--;
    } else {
      error = true;
      break;
    }
  }
  if (not error) {
    return errorI;
  }

  // Test ErrorJ
  error = false;
  i = 0;
  j = s.size() - 1;
  while (i <= j) {
    if (j == errorJ) {
      j--;
      continue;
    }
    if (s[i] == s[j]) {
      i++;
      j--;
    } else {
      error = true;
      break;
    }
  }
  if (not error) {
    return errorJ;
  }
  return -1; // Both are not palindrome
}

int main() {
  ofstream fout(getenv("OUTPUT_PATH"));

  string q_temp;
  getline(cin, q_temp);

  int q = stoi(ltrim(rtrim(q_temp)));

  for (int q_itr = 0; q_itr < q; q_itr++) {
    string s;
    getline(cin, s);

    int result = palindromeIndex(s);

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
