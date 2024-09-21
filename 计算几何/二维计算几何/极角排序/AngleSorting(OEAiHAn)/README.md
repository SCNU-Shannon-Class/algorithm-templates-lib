# 无浮点极角排序

### 无浮点极角排序

对于有些题目给定点坐标均为整数，此时为避免浮点数的丢精度问题，可使用如下无需浮点运算的极角排序，使用时直接将 `cmp` 传入 `sort` 函数即可。

```c++
int qua(pll p)
{
    if (p.first > 0 && p.second >= 0)
        return 0;
    else if (p.first <= 0 && p.second > 0)
        return 1;
    else if (p.first < 0 && p.second <= 0)
        return 2;
    else
        return 3;
}

bool cmp(pll& l, pll& r)
{
    if (qua(l) != qua(r))
        return qua(l) < qua(r);
    else
        return cross(l, r) > 0;
}
```

如仅需对斜率进行排序，稍作修改即可。

### 自定义原点

`p` 为点的坐标，`o` 为自定义的原点下标，排序时应保证所有点的原点相同，需以 `o` 为原点进行极角排序时直接使用 `sort` 排序即可。

```c++
struct pwo
{
    pll p, o;
    
    bool operator < (pwo &r)
    {
        if (qua(p - o) != qua(r.p - r.o))
            return qua(p - o) < qua(r.p - r.o);
        else
            return cross(p - o, r.p - r.o) > 0;
    }
    
    pwo(pll p, pll o)
    {
        this->p = p;
        this->o = o;
    }
    pwo() {};
}
```