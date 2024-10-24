#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'findMedian' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

int bin_index(int value) { return value + 10'000; }

int findMedian(vector<int> arr) {
  int n = arr.size();
  sort(arr.begin(), arr.end());
  return arr[n / 2];

  // Method2: Use counting sort

  // int median_index = n / 2;
  // // [median_index 개의 element] [ans] [...]

  // int count_sort[20050];
  // for (int i = 0; i < 20040; i++) {
  //   count_sort[i] = 0;
  // }

  // for (int i = 0; i < arr.size(); i++) {
  //   count_sort[bin_index(arr[i])] += 1;
  // }

  // int smaller = 0;
  // int i;
  // for (i = -10'000; i <= 10'000; i++) {
  //   smaller += count_sort[bin_index(arr[i])];
  //   // 0 0 [1]: median_index=2, smaller=2
  //   // 0 0 [0]: median_index=2, smaller=3
  //   if (median_index < smaller) {
  //     break;
  //   }
  // }
  // return i;
}

int main() {
  ofstream fout(getenv("OUTPUT_PATH"));

  string n_temp;
  getline(cin, n_temp);

  int n = stoi(ltrim(rtrim(n_temp)));

  string arr_temp_temp;
  getline(cin, arr_temp_temp);

  vector<string> arr_temp = split(rtrim(arr_temp_temp));

  vector<int> arr(n);

  for (int i = 0; i < n; i++) {
    int arr_item = stoi(arr_temp[i]);

    arr[i] = arr_item;
  }

  int result = findMedian(arr);

  fout << result << "\n";

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
