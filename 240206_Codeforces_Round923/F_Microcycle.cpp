#include <algorithm>
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

struct Edge {
  int u, v, w;
};

#pragma region DSU
struct Node {
  int parent, rank;
};
vector<Node> disjointSet;
Node &node(int index) { return disjointSet[index]; }
bool isRoot(int index) { return node(index).parent == index; }
// find == getRoot
int find(int index) {
  if (isRoot(index)) {
    return index;
  }
  node(index).parent = find(node(index).parent);
  return node(index).parent;
}
bool onSameSet(int indexA, int indexB) { return find(indexA) == find(indexB); }
void doUnion(int indexA, int indexB) {
  if (onSameSet(indexA, indexB)) {
    return;
  }

  int rootA = find(indexA);
  int rootB = find(indexB);

  // Merge: small to large
  if (node(rootA).rank > node(rootB).rank) {
    swap(rootA, rootB);
  }
  // Now nodeA.rank <= nodeB.rank
  node(rootA).parent = rootB; // Merge
  if (node(rootA).rank == node(rootB).rank) {
    node(rootB).rank += 1;
  }
}
#pragma endregion

#pragma region DFS
vector<vector<int>> graph;
vector<bool> visited;
vector<int> path;

bool dfs(int node, int destination) {
  visited[node] = true;

  if (node == destination) {
    return true;
  }

  for (auto &&v : graph[node]) {
    if (not visited[v]) {
      path.push_back(v);
      bool result = dfs(v, destination);
      if (result) {
        return true; // Preserve path when found
      }
      path.pop_back();
    }
  }

  return false;
}
#pragma endregion

void solve(int testcase) {
  int n, m;
  cin >> n >> m;
  vector<Edge> edges(m);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    edges[i] = {u, v, w};
  }

  // 1. Disjoint Set Union: Find minimal edge that completes cycle
  auto willBeTrue = [](const Edge &front, const Edge &back) -> bool {
    return front.w > back.w;
  };
  sort(edges.begin(), edges.end(), willBeTrue);

  disjointSet = vector<Node>(n + 1);
  for (int i = 1; i <= n; ++i) {
    // init: parent = self, rank = 1
    disjointSet[i] = {i, 1};
  }

  Edge minimalEdge;
  for (auto &&edge : edges) {
    if (onSameSet(edge.u, edge.v)) {
      minimalEdge = edge;
    } else {
      doUnion(edge.u, edge.v);
    }
  }

  // 2. DFS: Find simple path from -> to without minimalEdge
  //         -> from --(path)-- to --(minimalEdge)-- from
  graph = vector<vector<int>>(n + 1);
  for (auto &&edge : edges) {
    if (edge.u == minimalEdge.u and edge.v == minimalEdge.v) {
      continue;
    }
    graph[edge.u].push_back(edge.v);
    graph[edge.v].push_back(edge.u);
  }
  visited = vector<bool>(n + 1, false);
  path = vector<int>();

  int from = minimalEdge.u;
  int to = minimalEdge.v;
  path.push_back(from);
  dfs(from, to);

  cout << minimalEdge.w << " " << path.size() << "\n";
  for (auto &&u : path) {
    cout << u << " ";
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