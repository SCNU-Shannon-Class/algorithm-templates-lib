# 并查集
**从0开始计数**
+ **init**构造$[0, n), 即[0, n-1]$的并查集
+ **构造函数**调用init
+ **find**找到x所在集合祖先
+ **same**判断x和y是否在一个集合
+ **merge**将x和y放在一个集合，返回是否进行过合并操作。
+ **size**返回x所在集合的大小

```C++
struct DSU {
    std::vector<int> f, siz;
    
    DSU() {}
    DSU(int n) {
        init(n);
    }
    
    void init(int n) {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }
    
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    
    int size(int x) {
        return siz[find(x)];
    }
};
```

使用例:
[P3367](P3367.md)

# 带权并查集
+ **路径压缩**:如果点未被压缩dis为到父节点距离，否则为到根距离（更新方式：父节点距离+父节点到根距离）
+ **合并x,y且保证$val_x - val_y=d$**：
  1. 如果两点在同一集合，则判断两点的距离是否为d。有：$\\ val_x=val_f+d_x\\ val_y=val_f+d_y \\ 则 val_x - val_y = d_x - d_y$
  2. 如果两点不在同一集合，则合并fx,fy并且计算fx到fy的距离:$\\ val_x=val_{fx}+d_x\\ val_y=val_{fy}+d_y \\ val_x - val_y = d \\ 则有val_{fx} + d_x - val_{fy}-d_y=d \\所以val_{fx} - val{fy} = d+d_y-d_x$
+ 求点的距离一定先压缩路径后再求
```cpp
template<class T>
struct DSU {
    std::vector<int> f, siz;
    std::vector<T> dis;
    DSU() {}
    DSU(int n) {
        init(n);
    }
    
    void init(int n) {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
        dis.assign(n, T());
    }
    
    int find(int x) {
        if (x != f[x]) {
            int fa = f[x];
            f[x] = find(f[x]);
            dis[x] = dis[x] + dis[fa];
        }
        return f[x];
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }

    bool DisSame(int x, int y){
        return (find(x) == find(y)) && (dis[x]==dis[y]);
    }
    
    int merge(int x, int y, T d=T()) {
        int fx = find(x);
        int fy = find(y);
        if (fx == fy) {
            T set_d = dis[x] - dis[y];
            if (set_d == d){
                return 0;
            }
            else{
                return -1;
            }
        }
        else{
            f[fx] = fy;
            dis[fx] = d + dis[y] - dis[x];
            siz[fy] += siz[fx];
            return 1;
        }
    }
    
    int size(int x) {
        return siz[find(x)];
    }

    T getdis(int x){
        find(x);
        return dis[x];
    }
};
```

# 可回退并查集
如果期望并查集像栈一样回退（即回退操作不能撤销）
则使用启发式合并（按照大小判断）合并操作只会修改一个点的大小和父节点。此时维护修改的点和修改前的值即可回退
```cpp
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
```