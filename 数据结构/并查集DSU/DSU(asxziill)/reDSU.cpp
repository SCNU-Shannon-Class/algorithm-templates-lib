struct DSU {
  std::vector<int> siz, f;
  std::vector<std::pair<int *, int>> his;
  DSU(int n) : siz(n, 1), f(n) { std::iota(f.begin(), f.end(), 0); }
  bool merge(int u, int v) {
      u = find(u), v = find(v);
      if (u == v) return false;
      if (siz[u] < siz[v]) std::swap(u, v);
      his.emplace_back(&siz[u], siz[u]);
      siz[u] += siz[v];
      his.emplace_back(&f[v], f[v]);
      f[v] = u;
      return true;
  }
  int find(int x) {
      while (x != f[x]) x = f[x];
      return x;
  }
  int size(int x) { return siz[find(x)]; }
  void undo(int x) {
      while (int(his.size()) > x) {
          *his.back().first = his.back().second;
          his.pop_back();
      }
  }
};