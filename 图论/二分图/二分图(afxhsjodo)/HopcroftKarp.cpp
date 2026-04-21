#include <bits/stdc++.h>

using namespace std;

// 复杂度 O(E \times \sqrt(n + m))，边数乘点数开方
class HopcroftKarp {
   public:
    int n, m;  // 左部 n，右部 m
    std::vector<std::vector<int>> g;
    std::vector<int> dist, matchL, matchR;

    HopcroftKarp(int n, int m) : n(n), m(m) {
        g.resize(n);
        matchL.assign(n, -1);
        matchR.assign(m, -1);
        dist.resize(n);
    }

    void addEdge(int u, int v) {
        // 0 <= u < n; 0 <= v < m
        g[u].push_back(v);
    }

    int maxMatching() {
        int res = 0;
        while (bfs()) {
            for (int i = 0; i < n; i++) {
                if (matchL[i] == -1 && dfs(i)) {
                    res++;
                }
            }
        }
        return res;
    }

   private:
    bool bfs() {
        std::queue<int> q;
        for (int i = 0; i < n; i++) {
            if (matchL[i] == -1) {
                dist[i] = 0;
                q.push(i);
            } else {
                dist[i] = -1;
            }
        }

        bool found = false;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                int nxt = matchR[v];
                if (nxt != -1 && dist[nxt] == -1) {
                    dist[nxt] = dist[u] + 1;
                    q.push(nxt);
                }
                if (nxt == -1) {
                    found = true;
                }
            }
        }
        return found;
    }

    bool dfs(int u) {
        for (int v : g[u]) {
            int nxt = matchR[v];
            if (nxt == -1 || (dist[nxt] == dist[u] + 1 && dfs(nxt))) {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }
};

void solve() {
    int n, m, e;
    cin >> n >> m >> e;
    HopcroftKarp hk(n, m);
    while (e--) {
        int u, v;
        cin >> u >> v;
        // 注意左闭右开
        hk.addEdge(u - 1, v - 1);
    }
    cout << hk.maxMatching() << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}