#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;
typedef long long ll;

const int N_const = 200'005;
int p[N_const];
int q[N_const];
ll modNum = 998'244'353;

ll inversionCount;
void merge(vector<int> &arr, vector<int> &temp, int aStart, int aEnd,
           int bEnd) {
  int a = aStart;
  int b = aEnd + 1;
  int p = aStart;

  while (a <= aEnd or b <= bEnd) {
    if (a > aEnd) {
      temp[p] = arr[b];
      p++;
      b++;
    } else if (b > bEnd) {
      temp[p] = arr[a];
      p++;
      a++;
    } else if (arr[a] <= arr[b]) {
      temp[p] = arr[a];
      p++;
      a++;
    } else { // arr[a] > arr[b]
      temp[p] = arr[b];
      p++;
      b++;
      inversionCount += (aEnd - a + 1);
    }
  }

  for (int p = aStart; p <= bEnd; ++p) {
    arr[p] = temp[p];
  }
}

void merge_sort(vector<int> &arr, vector<int> &temp, int start, int end) {
  if (start >= end) {
    return;
  }
  int mid = (start + end) / 2;
  merge_sort(arr, temp, start, mid);
  merge_sort(arr, temp, mid + 1, end);
  // invariant: `arr[start..mid]`, `arr[mid+1..end]` is sorted
  merge(arr, temp, start, mid, end);
  // result: `arr[start..end]` is sorted
}

void solve(int testcase) {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; ++i) {
    cin >> p[i];
  }

  for (int i = 0; i < k; ++i) {
    cin >> q[i];
  }

  // p[i]: permutation of [1, 3, 5, ... 2n - 1]
  // q[i]: permutation of [0, 1, 2, ... k - 1]

  ll result = 0;
  // a[i * k + j] = p[i] * 2^q[j]
  // find number of all inversion pair (i, j)
  // a: n row * k col
  
  // 1. Find inversion of Q
  vector<int> q_sorted(q, q + k);
  vector<int> temp(k);
  inversionCount = 0;
  merge_sort(q_sorted, temp, 0, k - 1);
  // inversionCount = q inversion count within a row
  result += inversionCount * n;

  cout << result << "\n";
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