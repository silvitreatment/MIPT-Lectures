#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

vector<int> graph[MAXN];
vector<bool> visited;
vector<bool> onStack;
vector<int> result;
bool hasCycle = false;

void dfs(int u) {
    visited[u] = true;
    onStack[u] = true;

    for (int v : graph[u]) {
        if (hasCycle) return;
        if (!visited[v]) {
            dfs(v);
        } else if (onStack[v]) {
            hasCycle = true; // Найдена обратная дуга — цикл
            return;
        }
    }

    onStack[u] = false;
    result.push_back(u);
}

vector<int> topologicalSort(int n) {
    visited.assign(n, false);
    onStack.assign(n, false);
    result.clear();
    hasCycle = false;

    for (int v = 0; v < n; ++v) {
        if (!visited[v]) {
            dfs(v);
        }
    }

    if (hasCycle) {
        cout << "Граф содержит цикл, топологическая сортировка невозможна.\n";
        return {};
    }

    reverse(result.begin(), result.end());
    return result;
}
