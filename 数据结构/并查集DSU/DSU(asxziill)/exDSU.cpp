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
