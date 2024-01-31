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

int answer[300'005]; // [0..q-1]

#pragma region Disjoint Set DataStructure

using Index = tuple<Pos, int>;

struct Node {
  Index parent;
  int rank;
  set<int> queryIndexSet;
};

// UF[r][c][parity] = parent, rank, querySet
class DisjointSet : vector<vector<vector<Node>>> {

  // Base Methods
  Node &ref(Index index) {
    auto [pos, parity] = index;
    auto [r, c] = pos;
    return (*this)[r][c][parity];
  }
  Index &parent(Index index) { return ref(index).parent; }
  int &myRank(Index index) { return ref(index).rank; }
  set<int> &mySet(Index index) { return ref(index).queryIndexSet; }

  bool isRoot(Index index) { return index == parent(index); }

public:
  // vector of [0..N-1][0..M-1][0..K]
  DisjointSet(int N, int M, int K)
      : vector<vector<vector<Node>>>(N,
                                     vector<vector<Node>>(M, vector<Node>(K))) {
    for (int r = 0; r < N; ++r) {
      for (int c = 0; c < M; ++c) {
        for (int parity = 0; parity < K; ++parity) {
          // parent = self, rank = 1
          Index index = {{r, c}, parity};
          ref(index) = {index, 1, set<int>()};
        }
      }
    }
  }

  // findRoot (while doing path compression)
  Index findRoot(Index index) {
    if (not isRoot(parent(index))) {
      parent(index) = findRoot(parent(index));
      // rank is meaningless for non-root element
    }
    return parent(index);
  }

  // if two nodes are already in union
  bool isUnion(Index indexA, Index indexB) {
    Index rootA = findRoot(indexA);
    Index rootB = findRoot(indexB);

    return rootA == rootB;
  }

  // merge two nodes
  void doUnion(Index indexA, Index indexB, int safety) {
    Index rootA = findRoot(indexA);
    Index rootB = findRoot(indexB);

    if (isUnion(rootA, rootB)) {
      return;
    }

    // Check rank for small to large merge
    if (myRank(rootA) < myRank(rootB)) {
      std::swap(rootA, rootB);
    }

    // now rootA is large, rootB is small
    // 1. Merge parent
    parent(rootB) = rootA;
    // 2. Merge rank
    if (myRank(rootA) == myRank(rootB)) {
      myRank(rootA) += 1;
    }
    // 3. Merge queryIndexSet
    // Check if query target (x, y) has merged now by token
    set<int> &setA = mySet(rootA);
    for (auto &&i : mySet(rootB)) {
      if (setA.count(i) == 1) {
        setA.erase(i);
        answer[i] = safety;
      } else {
        // If not merged, move token to new root
        setA.insert(i);
      }
    }
  }

  void mySetInsert(Index index, int item) { mySet(index).insert(item); }
};

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
  // 2. Create disjoint set with (row, column, parity)
  // 3. For query target (x, y), mark token: add queryIndex for both parity
  // 4. Disjoint Set Union: Search path with tiles >= safety x
  //    Check tile with safety x. If move to neighbor is possible then union
  //    -> If (x, y, 0) and (x, y, 1) is in same set, then loop path exists
  // 4-1. When move, check if move crossed the line then invert parity.
  // 4-2. When union, check queryIndex set and find duplicate.
  //      If duplicate, then (x, y, 0) and (x, y, 1) became same set.
  //
  // Draw line from rightmost island to right so that it can reach grid.
  // A point(rightmost island) is in polygon(path) iff path crossed the line odd
  // numbers of time.

  auto safetyMap = calculateSafetyMap(map);

  vector<vector<Pos>> safety_pos(safetyMax + 1); // [0..safetyMax]
  for (int r = 1; r <= n; ++r) {
    for (int c = 1; c <= m; ++c) {
      if (map[r][c] == Tile::VOLCANO or map[r][c] == Tile::OCEAN) {
        safety_pos[safetyMap[r][c]].push_back({r, c});
      }
    }
  }

  DisjointSet disjoint_set(n + 1, m + 1, 2); //[1..n][1..m][0, 1]

  for (int qIndex = 0; qIndex < q; ++qIndex) {
    int x, y;
    cin >> x >> y;

    disjoint_set.mySetInsert({{x, y}, 0}, qIndex);
    disjoint_set.mySetInsert({{x, y}, 1}, qIndex);
  }

  auto deltaArray = array<Pos, 4>{Pos{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  auto [islandR, islandC] = islandRightmost;

  // Union high safety first, for maximum safety
  for (int safety = safetyMax; safety >= 0; --safety) {
    for (auto &&pos : safety_pos[safety]) {
      auto [r, c] = pos;
      for (auto &&[dr, dc] : deltaArray) {
        int r2 = r + dr, c2 = c + dc;

        if (not(map[r2][c2] == Tile::OCEAN or map[r2][c2] == Tile::VOLCANO)) {
          continue;
        }
        // Able to Move
        if (not(safetyMap[r2][c2] >= safety)) {
          continue;
        }
        // Able to move in safety

        if ((islandR == r or islandR == r2) and
            (islandR - 1 == r or islandR - 1 == r2) and
            (c > islandC and c2 > islandC)) {
          // If move crossed the line: invert parity
          disjoint_set.doUnion({pos, 0}, {{r2, c2}, 1}, safety);
          disjoint_set.doUnion({pos, 1}, {{r2, c2}, 0}, safety);
        } else {
          // If move didn't cross the line: preserve parity
          disjoint_set.doUnion({pos, 0}, {{r2, c2}, 0}, safety);
          disjoint_set.doUnion({pos, 1}, {{r2, c2}, 1}, safety);
        }
      }
    }
  }

  for (int i = 0; i < q; ++i) {
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