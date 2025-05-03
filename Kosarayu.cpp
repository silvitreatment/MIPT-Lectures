#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

vector<int> G[MAXN];  // Исходный граф
vector<int> H[MAXN];  // Транспонированный граф (инвертированный)
vector<bool> visited;
vector<int> ord;      // Порядок выхода из dfs1
vector<int> component;
int col = 1;

void dfs1(int v) {
    visited[v] = true;
    for (int u : G[v]) {
        if (!visited[u]) {
            dfs1(u);
        }
    }
    ord.push_back(v);
}

void dfs2(int v) {
    component[v] = col;
    for (int u : H[v]) {
        if (component[u] == 0) {
            dfs2(u);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m; // n — количество вершин, m — количество рёбер

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);   // Ребро u → v в исходном графе
        H[v].push_back(u);   // Ребро v → u в транспонированном графе
    }

    visited.assign(n, false);
    component.assign(n, 0);

    // Первый проход — по исходному графу
    for (int u = 0; u < n; ++u) {
        if (!visited[u]) {
            dfs1(u);
        }
    }

    // Второй проход — по транспонированному графу
    reverse(ord.begin(), ord.end());
    for (int u : ord) {
        if (component[u] == 0) {
            dfs2(u);
            col++;
        }
    }

    // Вывод компонент:
    cout << "Компоненты сильной связности:\n";
    for (int v = 0; v < n; ++v) {
        cout << "Вершина " << v << " в компоненте " << component[v] << '\n';
    }

    return 0;
}
