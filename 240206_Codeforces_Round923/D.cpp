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

struct Res {
  int i, j;
  int value; // 0: different
};

int a[200'005];
Res tree[4 * 200'005];

int left(int node) { return 2 * node; }
int right(int node) { return 2 * node + 1; }

Res construct(int node, int myLeft, int myRight) {
  if (myLeft == myRight) {
    tree[node] = {-1, -1, a[myLeft]};
    return tree[node];
  }

  int mid = (myLeft + myRight) / 2;
  auto [l_i, l_j, l_value] = construct(left(node), myLeft, mid);
  auto [r_i, r_j, r_value] = construct(right(node), mid + 1, myRight);

  if (l_value != 0 and r_value != 0) {
    // left is same, right is same
    if (l_value == r_value) {
      tree[node] = {-1, -1, l_value};
    } else {
      tree[node] = {myLeft, myRight, 0};
    }
    return tree[node];
  }
  if (l_value == 0) {
    // left is different
    tree[node] = {l_i, l_j, 0};
    return {l_i, l_j, 0};
  }
  // right is different
  tree[node] = {r_i, r_j, 0};
  return {r_i, r_j, 0};
}

Res query_same(int node, int myLeft, int myRight, int searchL, int searchR) {
  // Assume: [ [  search  ] my ]
  if (searchL <= myLeft and myRight <= searchR) {
    return tree[node];
  }
  if (searchR < myLeft or myRight < searchL) {
    return {-1, -1, -1};
  }

  int mid = (myLeft + myRight) / 2;
  auto [l_i, l_j, l_value] =
      query_same(left(node), myLeft, mid, searchL, searchR);
  auto [r_i, r_j, r_value] =
      query_same(right(node), mid + 1, myRight, searchL, searchR);

  if (l_value == 0) {
    // left is different
    return {l_i, l_j, 0};
  }
  if (r_value == 0) {
    // right is different
    return {r_i, r_j, 0};
  }

  if (l_value == -1) {
    l_value = r_value;
  }
  if (r_value == -1) {
    r_value = l_value;
  }

  // left is same, right is same
  if (l_value == r_value) {
    return {-1, -1, l_value};
  } else {
    // but different!
    return {max(myLeft, searchL), min(myRight, searchR), 0};
  }
}

void solve(int testcase) {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }

  // Construct Segment Tree
  construct(1, 1, n);

  int q;
  cin >> q;
  for (int _ = 0; _ < q; ++_) {
    int l, r;
    cin >> l >> r;

    auto [i, j, same] = query_same(1, 1, n, l, r);
    cout << i << " " << j << "\n";
  }
  cout << "\n";
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