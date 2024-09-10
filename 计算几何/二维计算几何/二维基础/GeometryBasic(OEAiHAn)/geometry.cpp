#include <bits/stdc++.h>
#include <unordered_map>
#define LL long long
#define pii pair<int, int>
#define pll pair<LL, LL>
#define double long double
#define pdd pair<double, double>
#define eps 1e-9

using namespace std;

pll operator + (pll l, pll r)
{
    return make_pair(l.first + r.first, l.second + r.second);
}

pll operator - (pll l, pll r)
{
    return make_pair(l.first - r.first, l.second - r.second);
}

LL dot(pll l, pll r)
{
    return l.first * r.first + l.second * r.second;
}

LL cross(pll l, pll r)
{
    return l.first * r.second - l.second * r.first;
}

double dis(pll v)
{
    return sqrt(dot(v, v));
}

struct line
{
    pdd p, v;
    double ang;

    line(pdd p, pdd v)
    {
        this->p = p;
        this->v = v;
        this->ang = atan2(v.second, v.first);
    }

    bool operator < (const line& r)
    {
        return this->ang < r.ang;
    }

    pdd getIntersection(line l, line r)
    {
        pdd t = r.p + r.v;
        double s1 = cross(l.v, r.p - l.p), s2 = cross(l.v, t - l.p);
        return make_pair((r.p.first * s2 - t.first * s1) / (s2 - s1), (r.p.second * s2 - t.second * s1) / (s2 - s1));
    }
};