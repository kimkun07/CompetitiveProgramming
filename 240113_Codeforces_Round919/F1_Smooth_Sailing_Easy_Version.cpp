#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;
using ll = long long;
using pos = tuple<int, int>; // r c

void printAns(bool yes) {
  if (yes) {
    cout << "Yes"
         << "\n";
  } else {
    cout << "No"
         << "\n";
  }
}

enum class Tile : char { GRID = 'x', OCEAN = '.', VOLCANO = 'v', ISLAND = '#' };

std::ostream &operator<<(std::ostream &out, const Tile &tile) {
  out << static_cast<char>(tile);
  return out;
}

template <typename T> void printArr(vector<vector<T>> &arr) {
  for (auto row : arr) {
    for (auto e : row) {
      cout << e << " ";
    }
    cout << endl;
  }
  cout << endl;
}

int getN(vector<vector<Tile>> &map) { return map.size() - 1; }
int getM(vector<vector<Tile>> &map) { return map.front().size() - 1; }

vector<vector<int>> calculateSafetyMap(vector<vector<Tile>> &map) {
  int n = getN(map), m = getM(map);

  queue<pos> bfsQueue;
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

  auto deltaArray = array<pos, 4>{pos{1, 0}, pos{-1, 0}, pos{0, 1}, pos{0, -1}};
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

// Use all tile >= safety
// when safety is 0, every tile is available
vector<vector<bool>> findPath(vector<vector<Tile>> &map,
                              vector<vector<int>> &safetyMap, pos start,
                              int safety) {
  int n = getN(map), m = getM(map);

  queue<pos> bfsQueue;
  vector<vector<bool>> visited(n + 2,
                               vector<bool>(m + 2, false)); // [0..n+1][0..m+1]
  vector<vector<bool>> path(n + 2,
                            vector<bool>(m + 2, false)); // [0..n+1][0..m+1]

  auto [r1, c1] = start;
  if (safetyMap[r1][c1] >= safety) {
    visited[r1][c1] = true;
    bfsQueue.push(start);
  }

  auto deltaArray = array<pos, 4>{pos{1, 0}, pos{-1, 0}, pos{0, 1}, pos{0, -1}};
  while (not bfsQueue.empty()) {
    auto [r, c] = bfsQueue.front();
    bfsQueue.pop();

    path[r][c] = true;

    for (const auto &[dr, dc] : deltaArray) {
      int r2 = r + dr, c2 = c + dc;
      if ((not visited[r2][c2]) and
          (map[r2][c2] == Tile::OCEAN or map[r2][c2] == Tile::VOLCANO)) {
        if (safetyMap[r2][c2] >= safety) {
          visited[r2][c2] = true;
          bfsQueue.push({r2, c2});
        }
      }
    }
  }

  return path; // Should use NRVP optimization
}

bool isValidPath(vector<vector<Tile>> &map, vector<vector<bool>> &path,
                 pos start) {
  int n = getN(map), m = getM(map);

  queue<pos> bfsQueue;
  vector<vector<bool>> visited(n + 2,
                               vector<bool>(m + 2, false)); // [0..n+1][0..m+1]

  auto [r1, c1] = start;
  visited[r1][c1] = true;
  bfsQueue.push(start);

  auto deltaArray =
      array<pos, 8>{pos{1, 0}, pos{-1, 0}, pos{0, 1},  pos{0, -1},
                    pos{1, 1}, pos{1, -1}, pos{-1, 1}, pos{-1, -1}};
  while (not bfsQueue.empty()) {
    auto [r, c] = bfsQueue.front();
    bfsQueue.pop();

    if (map[r][c] == Tile::GRID) {
      return false; // able to reach GRID
    }

    for (const auto &[dr, dc] : deltaArray) {
      int r2 = r + dr, c2 = c + dc;
      if ((not visited[r2][c2]) and (not path[r2][c2])) {
        visited[r2][c2] = true;
        bfsQueue.push({r2, c2});
      }
    }
  }

  return true;
}

void solve(int testcase) {
  int n, m, q;
  cin >> n >> m >> q;

  vector<vector<Tile>> map(n + 2,
                           vector<Tile>(m + 2, Tile::GRID)); // [0..n+1][0..m+1]
  // 0: grid, 1: Ocean, 2: Volcano, 3: Island
  pos islandCenter; // Remember any island tile

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
        islandCenter = {r, c};
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
  // 2. Binary search to maximize safety
  // 2-1. Find all available ocean from start position
  //      Can go anyway in path
  // 2-2. Check if path surround ISLAND completely
  //      -> bfs starting on ISLAND trying to reach GRID
  //      start and end of path should be connected horizontally or verically
  //      -> bfs can move diagonally

  auto safetyMap = calculateSafetyMap(map);

  for (int _ = 0; _ < q; ++_) {
    int x, y;
    cin >> x >> y;

    int l = 0, r = n + m;
    while (l <= r) {
      // l - 1: success
      // r + 1: fail
      int safety = (l + r) / 2;
      auto path = findPath(map, safetyMap, pos{x, y}, safety);
      bool isSuccess = isValidPath(map, path, islandCenter);
      if (isSuccess) {
        l = safety + 1;
      } else {
        r = safety - 1;
      }
    }

    // r(l-1): success, l(r+1): fail
    int ans = r;
    cout << ans << "\n";
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