#include <iostream>
#include <queue>
#include <set>
#include <tuple>
#include <vector>

using namespace std;
using ll = long long;
using Pos = tuple<int, int>; // r c

enum class Tile : char { GRID = 'x', OCEAN = '.', VOLCANO = 'v', ISLAND = '#' };

int getN(vector<vector<Tile>> &map) { return map.size() - 1; }
int getM(vector<vector<Tile>> &map) { return map.front().size() - 1; }

vector<vector<int>> calculateSafetyMap(vector<vector<Tile>> &map) {
  int n = getN(map), m = getM(map);

  queue<Pos> bfsQueue;
  vector<vector<bool>> visited(n + 2,
                               vector<bool>(m + 2, false)); // [0..n+1][0..m+1]
  vector<vector<int>> safetyMap(n + 2, vector<int>(m + 2)); // [0..n+1][0..m+1]

  for (int r = 1; r <= n; ++r) {
    for (int c = 1; c <= m; ++c) {
      if (map[r][c] == Tile::VOLCANO) {
        bfsQueue.push({r, c});
        safetyMap[r][c] = 0;
        visited[r][c] = true;
      }
    }
  }

  auto deltaArray = array<Pos, 4>{Pos{1, 0}, Pos{-1, 0}, Pos{0, 1}, Pos{0, -1}};
  while (not bfsQueue.empty()) {
    auto [r, c] = bfsQueue.front();
    bfsQueue.pop();

    for (const auto &[dr, dc] : deltaArray) {
      int r2 = r + dr, c2 = c + dc;
      if ((not visited[r2][c2]) and (map[r2][c2] != Tile::GRID)) {
        visited[r2][c2] = true;
        // We can set visited to true because only +1 can happen
        safetyMap[r2][c2] = safetyMap[r][c] + 1;
        bfsQueue.push({r2, c2});
      }
    }
  }

  return safetyMap;
}

// UF[r][c][parity] = parent, rank
#pragma region Union_Find DataStructure
using Node = tuple<Pos, int>;
using UF = vector<vector<vector<tuple<Node, int>>>>;
tuple<Node, int> &ref(UF &uf, Node node) {
  auto [pos, parity] = node;
  auto [r, c] = pos;
  return uf[r][c][parity];
}
Node &parent(UF &uf, Node node) { return std::get<0>(ref(uf, node)); }
int &myRank(UF &uf, Node node) { return std::get<1>(ref(uf, node)); }

bool isRoot(UF &uf, Node node) { return node == parent(uf, node); }

// findRoot with path compression
Node findRoot(UF &uf, Node node) {
  if (not isRoot(uf, parent(uf, node))) {
    parent(uf, node) = findRoot(uf, parent(uf, node));
    // rank is meaningless for non-root element
  }
  return parent(uf, node);
}

bool isUnion(UF &uf, Node nodeA, Node nodeB) {
  Node rootA = findRoot(uf, nodeA);
  Node rootB = findRoot(uf, nodeB);
  
  return rootA == rootB;
}

// QueryManager
using TT = vector<vector<vector<set<int>>>>;
set<int> &mySet(TT &tt, Node node) {
  auto [pos, parity] = node;
  auto [r, c] = pos;
  return tt[r][c][parity];
}
int answer[300'005]; // [0..q-1]

void doUnion(UF &uf, Node nodeA, Node nodeB, TT &tt, int safety) {
  Node rootA = findRoot(uf, nodeA);
  Node rootB = findRoot(uf, nodeB);
  
  if (isUnion(uf, rootA, rootB)) {
    return;
  }

  // small to large merge
  if (myRank(uf, rootA) < myRank(uf, rootB)) {
    swap(rootA, rootB);
  }

  // rootA is large, rootB is small
  if (myRank(uf, rootA) == myRank(uf, rootB)) {
    myRank(uf, rootA) += 1;
  }
  // Merge tt
  set<int> &setA = mySet(tt, rootA);
  for (auto &&i : mySet(tt, rootB)) {
    if (setA.count(i) == 1) {
      setA.erase(i);
      answer[i] = safety;
    } else {
      setA.insert(i);
    }
  }

  parent(uf, rootB) = rootA;
}
#pragma endregion

void solve(int testcase) {
  int n, m, q;
  cin >> n >> m >> q;
  const int safetyMax = (n - 1) + (m - 1);

  vector<vector<Tile>> map(n + 2,
                           vector<Tile>(m + 2, Tile::GRID)); // [0..n+1][0..m+1]
  // 0: grid, 1: Ocean, 2: Volcano, 3: Island
  Pos islandRightmost = {0, 0}; // Remember rightmost island tile

  for (int r = 1; r <= n; ++r) {
    for (int c = 1; c <= m; ++c) {
      char x;
      cin >> x;
      switch (x) {
      case '.':
        map[r][c] = Tile::OCEAN; // Ocean
        break;
      case 'v':
        map[r][c] = Tile::VOLCANO; // Volcano
        break;
      case '#':
        map[r][c] = Tile::ISLAND; // Island
        if (c >= get<1>(islandRightmost)) {
          islandRightmost = {r, c};
        }
        break;
      default:
        throw std::runtime_error("Wrong Input: " + to_string(x));
        break;
      }
    }
  }

  // Solve
  // 1. Precompute safety of tile
  //    -> bfs start from volcano

  auto safetyMap = calculateSafetyMap(map);

  vector<vector<Pos>> safety_pos(safetyMax + 1); // [0..safetyMax]
  for (int r = 1; r <= n; ++r) {
    for (int c = 1; c <= m; ++c) {
      if (map[r][c] == Tile::VOLCANO or map[r][c] == Tile::OCEAN) {
        safety_pos[safetyMap[r][c]].push_back({r, c});
      }
    }
  }

  UF union_find(n + 1,
                vector<vector<tuple<Node, int>>>(
                    m + 1, vector<tuple<Node, int>>(2))); //[1..n][1..m][0, 1]
  // init UF
  for (int r = 1; r <= n; ++r) {
    for (int c = 1; c <= m; ++c) {
      for (int parity = 0; parity <= 1; ++parity) {
        // parent = self, rank = 1
        union_find[r][c][parity] = {{{r, c}, parity}, 1};
      }
    }
  }

  TT tt(n + 1, vector<vector<set<int>>>(m + 1, vector<set<int>>(2))); // [1..n][1..m][0, 1]
  for (int qIndex = 0; qIndex < q; ++qIndex) {
    int x, y;
    cin >> x >> y;
    
    mySet(tt, {{x, y}, 0}).insert(qIndex);
    mySet(tt, {{x, y}, 1}).insert(qIndex);
  }

  auto deltaArray = array<Pos, 4>{Pos{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  auto [islandR, islandC] = islandRightmost;

  for (int safety = safetyMax; safety >= 0; --safety) {
    for (auto &&pos : safety_pos[safety]) {
      auto [r, c] = pos;
      for (auto &&[dr, dc] : deltaArray) {
        int r2 = r + dr, c2 = c + dc;
        if ((map[r2][c2] == Tile::OCEAN or map[r2][c2] == Tile::VOLCANO) and
            safetyMap[r2][c2] >= safety) {
          // Able to move in safety
          if ((islandR == r or islandR == r2) and
              (islandR - 1 == r or islandR - 1 == r2) and
              (c > islandC and c2 > islandC)) {
            // Cross the line
            doUnion(union_find, {pos, 0}, {{r2, c2}, 1}, tt, safety);
            doUnion(union_find, {pos, 1}, {{r2, c2}, 0}, tt, safety);
          } else {
            doUnion(union_find, {pos, 0}, {{r2, c2}, 0}, tt, safety);
            doUnion(union_find, {pos, 1}, {{r2, c2}, 1}, tt, safety);
          }
        }
      }
    }
  }
  
  for(int i = 0; i < q; ++i){
    cout << answer[i] << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  // int T;
  // cin >> T;
  // for (int t = 1; t <= T; ++t) {
  //   solve(t);
  // }
  solve(1);
  return 0;
}