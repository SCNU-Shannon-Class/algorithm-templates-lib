#include <bits/stdc++.h>
#include <unordered_map>
#define LL long long
#define pii pair<int, int>
#define pll pair<LL, LL>
#define double long double
#define pdd pair<double, double>
#define eps 1e-9

using namespace std;

pll operator - (pll l, pll r)
{
    return make_pair(l.first - r.first, l.second - r.second);
}

LL cross(pll l, pll r)
{
    return l.first * r.second - l.second * r.first;
}

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