#include <bits/stdc++.h>
#include <unordered_map>
#define LL long long
#define pll pair<LL, LL>

using namespace std;

struct line
{
    pll k, d;

    //两点相连直线
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
        LL g = __gcd(d.first, d.second);
        d.first /= g;
        d.second /= g;
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

    //rot为true时构造两点中垂线
    line(pll l, pll r, bool rot)
    {
        if (!rot)
        {
            line(l, r);
            return;
        }

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
        LL g = __gcd(d.first, d.second);
        d.first /= g;
        d.second /= g;
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

    bool cmp(const pll& l, const pll& r) const
    {
        return l.first * r.second < l.second * r.first;
    }

    bool operator < (const line& r) const
    {
        return cmp(this->d, r.d) || this->d == r.d && cmp(this->k, r.k);
    }
};

set<line> st;
map<line, int> mp;
