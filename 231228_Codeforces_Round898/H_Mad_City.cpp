#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

using namespace std;
typedef long long ll;
int n;

// note: 1 <= u, v <= n

pair<bool, set<int>> failure() { return make_pair(false, set<int>()); }

pair<bool, set<int>> dfs_findCycle(int u, vector<vector<int>> road,
                                   vector<bool> &visited, vector<bool> &onTrack,
                                   stack<int> &track) {
  if (onTrack[u]) {
    // found
    set<int> cycle;
    while (not track.empty()) {
      int v = track.top();
      track.pop();

      cycle.insert(v);
      if (v == u) {
        return make_pair(true, cycle);
      }
    }

    return failure();
  }
  if (visited[u]) {
    return failure();
  }

  visited[u] = true;
  onTrack[u] = true;
  int prev = (track.empty()) ? 0 : track.top();
  track.push(u);

  for (auto &&v : road[u]) {
    if (prev == v) {
      // just came from prev to v. not going backward.
      continue;
    }

    auto result = dfs_findCycle(v, road, visited, onTrack, track);
    if (result.first) {
      // Found
      return result;
    }
  }

  onTrack[u] = false;
  track.pop();

  return failure();
}

set<int> findCycle(vector<vector<int>> road) {
  vector<bool> visited(n + 1, false);
  vector<bool> onTrack(n + 1, false);
  stack<int> st;
  for (int i = 1; i <= n; ++i) {
    auto result = dfs_findCycle(i, road, visited, onTrack, st);
    if (result.first) {
      return result.second;
    }
  }
  return set<int>(); // Not reachable (always has cycle)
}

int dfs_findEntry(int u, vector<vector<int>> road, vector<bool> &visited,
                  set<int> &circle) {
  if (circle.contains(u)) {
    return u;
  }
  if (visited[u]) {
    return 0;
  }

  visited[u] = true;
  for (auto &&v : road[u]) {
    int result = dfs_findEntry(v, road, visited, circle);
    if (result != 0) {
      return result;
    }
  }

  return 0;
}

int findCost(vector<vector<int>> road, int from, int to) {
  queue<pair<int, int>> bfsQueue;
  vector<bool> visited(n + 1, false);
  bfsQueue.push(pair(from, 0));
  while (not bfsQueue.empty()) {
    auto [u, cost] = bfsQueue.front();
    bfsQueue.pop();
    if (u == to) {
      return cost;
    }
    visited[u] = true;

    for (auto &&v : road[u]) {
      if (visited[v]) {
        continue;
      }
      bfsQueue.push(pair(v, cost + 1));
    }
  }

  return 0; // Unreachable Code
}

void solve(int testcase) {
  int a, b;
  cin >> n >> a >> b;
  vector<vector<int>> road(n + 1); // road[u] = v -> (u, v)
  for (int i = 0; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    road[u].push_back(v);
    road[v].push_back(u);
  }

  // a will catch b
  // n edges -> exactly one cycle
  // b should get into entry of circle before a stands there

  // DFS with stack to find circle
  set<int> circle = findCycle(road);

  // DFS to search entry point of b
  vector<bool> visited(n + 1, false);
  int entry = dfs_findEntry(b, road, visited, circle);

  // a stands first
  int bSave = findCost(road, b, entry);
  int aStand = findCost(road, a, entry);
  string result = (aStand <= bSave) ? "NO" : "YES";

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