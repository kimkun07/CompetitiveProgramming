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
  int i, j;  // only valid when different: position of different
  int value; // 0: different. when same: the same value

  bool is_same() { return value != 0; }
  static Res make_same(int value) { return {-1, -1, value}; }
};

int a[200'005];
Res tree[4 * 200'005];

int left(int node) { return 2 * node; }
int right(int node) { return 2 * node + 1; }

Res construct(int node, int myLeft, int myRight) {
  if (myLeft == myRight) {
    // Leaf Node
    tree[node] = Res::make_same(a[myLeft]);
    return tree[node];
  }

  int mid = (myLeft + myRight) / 2;
  auto lRes = construct(left(node), myLeft, mid);
  auto rRes = construct(right(node), mid + 1, myRight);

  if (lRes.is_same() and rRes.is_same()) {
    // left is same, right is same
    if (lRes.value == rRes.value) {
      // left == right
      tree[node] = Res::make_same(lRes.value);
    } else {
      // left != right
      tree[node] = {myLeft, myRight, 0};
    }
  } else if (not lRes.is_same()) {
    // left is different
    tree[node] = lRes;
    return tree[node];
  } else {
    // right is different
    tree[node] = rRes;
  }

  return tree[node];
}

Res query(int node, int myLeft, int myRight, int searchL, int searchR) {
  // Assume: [ [  search  ] my ]
  if (searchL <= myLeft and myRight <= searchR) {
    // searchRange == my node range
    return tree[node];
  }

  int mid = (myLeft + myRight) / 2;
  // myLeft  mid  myRight
  Res lRes = (searchL <= mid)
                 ? query(left(node), myLeft, mid, searchL, min(searchR, mid))
                 : Res{-1, -1, -1};
  Res rRes = (mid + 1 <= searchR) ? query(right(node), mid + 1, myRight,
                                          max(searchL, mid + 1), searchR)
                                  : Res{-1, -1, -1};

  // Special Case: either left or right is invalid
  if (lRes.value == -1) {
    lRes = rRes;
  }
  if (rRes.value == -1) {
    rRes = lRes;
  }

  if (not lRes.is_same()) {
    // left is different
    return lRes;
  }
  if (not rRes.is_same()) {
    // right is different
    return rRes;
  }

  // left is same, right is same
  if (lRes.value == rRes.value) {
    // left == right
    return lRes;
  } else {
    // left != right
    // i = from left, j = from right
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

    auto [i, j, value] = query(1, 1, n, l, r);
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