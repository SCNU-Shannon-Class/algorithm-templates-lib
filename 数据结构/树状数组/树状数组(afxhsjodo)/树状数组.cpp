#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>
#include<string>
#include<map>
#include<unordered_map>
#include<set>
#include<cmath>
#include<stack>
#include<bitset>
#include<math.h>
#include <iomanip>
using namespace std;
#define lowbit(x) (x&(-x))
const int N = 32005;
struct Fenwick
{
    int n;
    vector<int>tr;
    Fenwick(int n = 0) { init(n); }
    void init(int n) { this->n = n; tr.assign(n + 1, 0); }
    void add(int x, int c)
    {
        for (int i = x; i <= n; i += lowbit(i))tr[i] += c;     
    }
    int sum(int x)
    {
        if (!x)return 0;
        int res = 0;
        for (int i = x; i; i -= lowbit(i))res += tr[i];
        return res;
    }
};

