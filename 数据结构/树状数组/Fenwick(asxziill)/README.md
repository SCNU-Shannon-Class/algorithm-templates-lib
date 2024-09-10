## 维护特点
+ 查询前缀和与修改，则数据只需有幺半群的性质就行
+ 区间查询要有逆运算

## 第k大
利用二叉搜索树类似的算法，因为子节点已经有子树大小信息了。树状数组当且仅当小标为$2^k$才存储子树的前缀和。
从0开始计算
+ 构造函数调用init
+ init构造大小为n从0开始计数的值为默认的树状数组
+ add位置x增加v
+ sum求$[0, x-1]$即$[0, x)$的值
+ rangeSum求$[l, r]$的值
+ kth求区间第k小**从0开始**
```C++
template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;
    
    Fenwick(int n = 0) {
        init(n);
    }
    
    void init(int n) {
        this->n = n;
        a.assign(n, T());
    }
    
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }
    
    T sum(int x) {
        auto ans = T();
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }
    
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
    
    int kth(T k) {
        int x = 0;
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && k >= a[x + i - 1]) {
                x += i;
                k -= a[x - 1];
            }
        }
        return x;
    }
};
```

## 使用例：[P3374](P3374.md)