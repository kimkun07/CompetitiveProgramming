#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;
typedef long long ll;

int a[2005];
int v[10'005];

class Stopwatch {
  typedef chrono::high_resolution_clock::time_point time_point;
  time_point start;
  vector<time_point> records;
  static time_point now() { return chrono::high_resolution_clock::now(); }
  map<string, time_point> starts;
  map<string, chrono::nanoseconds> time;

public:
  Stopwatch() { reset(); }
  void reset() {
    start = now();
    records.clear();
  }
  void lap() { records.push_back(now()); }
  void print() {
    using namespace chrono;
    for (int i = 0; i < records.size(); ++i) {
      auto elapsed = duration_cast<milliseconds>(records[i] - start);
      cout << setw(6) << elapsed.count() << "ms";
      if (i - 1 >= 0) {
        auto lap = duration_cast<milliseconds>(records[i] - records[i - 1]);
        cout << setw(6) << lap.count() << "ms";
      }
      cout << endl;
    }
  }
  void part_start(string name) { starts[name] = now(); }
  void part_end(string name) {
    time[name] = time[name] + chrono::duration_cast<chrono::nanoseconds>(
                                  now() - starts[name]);
  }
  void part_print() {
    for (auto &&i : time) {
      auto [name, value] = i;
      cout << setw(6) << name << setw(10) << value.count() << "ns" << endl;
    }
  }
};

vector<int> tree;

int parent(int node) { return node / 2; }
int left(int node) { return node * 2; }
int right(int node) { return node * 2 + 1; }
int root() { return 1; }
bool isRoot(int node) { return node == root(); }

// current node includes value[l..r]
// returns sum of value[start..end]
int treesumgo(tuple<int, int, int> node, int start, int end) {
  auto [index, l, r] = node;
  if (end < l or r < start) {
    return 0;
  }
  if (start <= l and r <= end) {
    return tree[index];
  }

  int m = (l + r) / 2;
  int left_sum = treesumgo(make_tuple(left(index), l, m), start, end);
  int right_sum = treesumgo(make_tuple(right(index), m + 1, r), start, end);
  return left_sum + right_sum;
}

int treeSum(tuple<int, int, int> rootNode, int start, int end) {
  return treesumgo(rootNode, start, end);
}

void treeUpdate(int node) {
  tree[node] += 1;
  if (not isRoot(node)) {
    treeUpdate(parent(node));
  }
}

void solve(int testcase) {
  int n, k, d;
  cin >> n >> k >> d;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= k; ++i) {
    cin >> v[i];
  }

  // n: 2000
  // k: 10^5
  // d: 10^9

  int h = (n == 1) ? 1 : (log2(n - 1) + 2);
  // n: 1 -> h = 1
  // n: 2 -> h = 2
  // n: 3 ~ 4 -> h = 3
  // n: 5 ~ 8 -> h = 4
  tree = vector<int>(pow(2, h) - 1 + 1, 0); // tree: 1 ~ 2^h-1
  int offset = pow(2, h - 1) - 1;
  // leafIndex = offset + 1 ~ offset + n
  int lastLeaf = offset + 1; // offset + 1 ~ offset + lastLeaf가 같은 층

  int result = 0;
  // day=2n까지만 flush를 참았을 때를 확인하면 된다.
  // flush를 참은 경우 최대 n까지 획득 가능한데,
  // 한 번도 안 참은 경우에도 2n일 동안 n만큼 획득할 수 있기 때문이다.
  for (int day = 1; day <= min(2 * n, d); ++day) {
    // day 일 때 처음 flush한 경우, 총점 scoreWhenFlush 획득
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
      int watered = treeSum(make_tuple(root(), 1, lastLeaf), i, n);
      if (a[i] + watered == i) {
        cnt += 1;
      }
    }
    // 한 번 flush한 이후에는 어차피 한 번에 1점 이상 획득할 수 없다.
    // acc -> flush -> acc -> flush 로 1점씩 획득하기
    int scoreWhenFlush = cnt + (d - day) / 2;
    result = max(scoreWhenFlush, result);

    // day 일 때까지 flush를 하지 않은 경우, 1..b acc
    const int b = v[(day - 1) % k + 1];
    const int leaf = offset + b;
    treeUpdate(leaf);
  }

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