# 无浮点截距式直线方程

### 截距式方程

用截距式方程存储直线，相比于前面用一个点和向量存储的直线，更易于区分多条直线之间的位置关系，一般为判断平行、重合等。

由于使用截距式方程在表示一些特殊直线时会出现问题（如与 x 轴、y 轴平行的直线），这里对这些特殊直线作特殊的唯一化处理。

### 无浮点处理

一般截距式方程中的斜率和截距不会恰好为整数，这里使用 `pair` 处理，以分数形式表示原本为用浮点数表示的斜率 $k$ 和截距 $d$。

```c++
struct line
{
    pll k, d;

    line(pll l, pll r)
    {
        LL dx = r.first - l.first, dy = r.second - l.second;
        if (!dx)
        {
            this->d = { l.first, 0 };
            this->k = { 1, 0 };
            return;
        }
        else if (!dy)
        {
            this->d = { l.second, 1 };
            this->k = { 0, 1 };
            return;
        }

        this->d = { l.second * dx - l.first * dy, dx };
        LL gcd = __gcd(d.first, d.second);
        d.first /= gcd;
        d.second /= gcd;
        if (d.first < 0)
        {
            d.first = -d.first;
            d.second = -d.second;
        }
        else if (!d.first)
            d.second = 1;

        this->k = { dx, dy };
        if (!k.first)
            k.second = 1;
        else if (!k.second)
            k.first = 1;
        else if (k.first < 0)
        {
            k.first = -k.first;
            k.second = -k.second;
        }
    }
    
    bool cmp(const pll& l, const pll& r) const
    {
        return l.first * r.second < l.second * r.first;
    }

    bool operator < (const line& r) const
    {
        return cmp(this->d, r.d) || this->d == r.d && cmp(this->k, r.k);
    }
};
```

使用时直接调用构造器构造结构体即可，已重载运算符 `<`，可将改结构体存入 `set`、`map` 等容器。

### 两点中垂线处理

如果要创建的直线不是两点相连形成的直线，而是两点间线段的垂直平分线，仅需对上面几个对 `d` 和 `k` 赋值的位置稍作修改。

```c++
struct line
{
    pll d, v;

    line(pll l, pll r)
    {
        LL dx = r.first - l.first, dy = r.second - l.second;

        if (!dx)
        {
            this->d = { (l.second + r.second) / (2 - (dy & 1)), 1 + (dy & 1) };
            this->k = { 1, 0 };
            return;
        }
        else if (!dy)
        {
            this->d = { 1 + (dx & 1), (l.first + r.first) / (2 - (dx & 1)) };
            this->k = { 0, 1 };
            return;
        }

        this->d = { (l.second + r.second) * dy + (l.first + r.first) * dx, dy * 2 };
        LL gcd = __gcd(d.first, d.second);
        d.first /= gcd;
        d.second /= gcd;
        if (d.first < 0)
        {
            d.first = -d.first;
            d.second = -d.second;
        }
        else if (!d.first)
            d.second = 1;

        this->k = { -dy, dx };
        if (!k.first)
            k.second = 1;
        else if (!k.second)
            k.first = 1;
        else if (k.first < 0)
        {
            k.first = -k.first;
            k.second = -k.second;
        }
    }
    
    bool cmp(pll l, pll r)
    {
        return l.first * r.second < l.second * r.first;
    }

    bool operator < (const line& r) const
    {
        return cmp(this->d, r.d) || this->d == r.d && cmp(this->v, r.v);
    }
};
```