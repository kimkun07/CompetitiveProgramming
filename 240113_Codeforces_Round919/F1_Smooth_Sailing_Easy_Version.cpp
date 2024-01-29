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

// safety 이상의 tile만 쓰기
vector<vector<bool>> findPath(int n, int m, vector<vector<Tile>> &map,
                              vector<vector<int>> &safetyMap, pos start,
                              int safety) {
  queue<pos> bfsQueue;
  vector<vector<bool>> visited(n + 2,
                               vector<bool>(m + 2, false)); // [0..n+1][0..m+1]

  vector<vector<bool>> result(n + 2,
                              vector<bool>(m + 2, false)); // [0..n+1][0..m+1]

  auto [r1, c1] = start;
  if (safetyMap[r1][c1] >= safety) {
    visited[r1][c1] = true;
    bfsQueue.push(start);
  }

  auto deltaArray = array<pos, 4>{pos{1, 0}, pos{-1, 0}, pos{0, 1}, pos{0, -1}};
  while (not bfsQueue.empty()) {
    auto [r, c] = bfsQueue.front();
    result[r][c] = true;
    bfsQueue.pop();

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

  return result; // Should use NRVP optimization
}

bool isValidPath(int n, int m, vector<vector<Tile>> &map,
                 vector<vector<bool>> &path, pos start) {
  queue<pos> bfsQueue;
  vector<vector<bool>> visited(n + 2,
                               vector<bool>(m + 2, false)); // [0..n+1][0..m+1]

  auto [r1, c1] = start;
  visited[r1][c1] = true;
  bfsQueue.push(start);

  auto deltaArray =
      array<pos, 8>{pos{1, 0}, pos{-1, 0}, pos{0, 1},  pos{0, -1},
                    pos{1, 1}, pos{-1, 1}, pos{-1, 1}, pos{-1, -1}};
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
  vector<vector<int>> safetyMap(n + 2, vector<int>(m + 2)); // [0..n+1][0..m+1]
  vector<vector<bool>> visited(n + 2,
                               vector<bool>(m + 2, false)); // [0..n+1][0..m+1]

  queue<pos> bfsQueue;
  pos islandCenter;

  char x;
  for (int r = 1; r <= n; ++r) {
    for (int c = 1; c <= m; ++c) {
      cin >> x;
      switch (x) {
      case '.':
        map[r][c] = Tile::OCEAN; // Ocean
        break;
      case 'v':
        map[r][c] = Tile::VOLCANO; // Volcano
        bfsQueue.push({r, c});
        safetyMap[r][c] = 0;
        visited[r][c] = true;
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

  // Preprocessing BFS
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

  for (int _ = 0; _ < q; ++_) {
    int x, y;
    cin >> x >> y;

    int l = 0, r = n + m;
    while (l <= r) {
      // l - 1: success
      // r + 1: fail
      int safety = (l + r) / 2;
      auto path = findPath(n, m, map, safetyMap, pos{x, y}, safety);
      bool isSuccess = isValidPath(n, m, map, path, islandCenter);
      if (isSuccess) {
        l = safety + 1;
      } else {
        r = safety - 1;
      }
    }
    // r(l-1): success, l(r+1): fail

    int ans = r; // == r + 1
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