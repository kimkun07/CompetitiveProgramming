#include <iostream>
#include <set>
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

bool dfs_cycle(int node, vector<set<int>> &graph, vector<bool> &visited_total,
               vector<bool> &visited_now) {
  visited_total[node] = true;
  visited_now[node] = true;

  for (auto &&v : graph[node]) {
    if (visited_now[v]) {
      return true; // there is a cycle
    } else if (visited_total[v]) {
      continue; // there is no cycle starting from v
    } else {
      bool result = dfs_cycle(v, graph, visited_total, visited_now);
      if (result) {
        return true;
      }
    }
  }

  visited_now[node] = false;
  return false;
}

bool findCycle(vector<set<int>> &graph) {
  int n = graph.size() - 1;

  vector<bool> visited_total(n + 1, false); // So we don't have to search again
  vector<bool> visited_now(n + 1, false);

  for (int i = 1; i <= n; ++i) {
    if (not visited_total[i]) {
      bool result = dfs_cycle(i, graph, visited_total, visited_now);
      if (result) {
        return true;
      }
    }
  }
  return false;
}

void solve(int testcase) {
  int n, k;
  cin >> n >> k;

  // Solve
  // For each screenshot, make a graph.
  // Contradiction of order results in cycle in graph.
  // If there is no contradiction, graph can be topologically sorted.
  // (Or there may be one node with no connection)

  vector<set<int>> graph(n + 1); // 1..n

  for (int i = 0; i < k; ++i) {
    int first;
    cin >> first;
    vector<int> ai(n - 1); // 0..(n-2)
    for (int j = 0; j < n - 1; ++j) {
      cin >> ai[j];
    }

    for (int j = 0; j <= n - 2 - 1; ++j) {
      // ai[j] -> ai[j + 1] connect
      graph[ai[j]].insert(ai[j + 1]);
    }
  }

  printAns(not findCycle(graph));
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