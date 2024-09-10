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