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

#define T_T 0 
#define nmsl cout<<"\nnmsl\n";//农贸税率
#define endl "\n"
#define pb push_back
#define x first 
#define y second
#define lowbit(x) (x&(-x))
#define ls u<<1
#define rs u<<1|1
typedef long long ll;
typedef ll LL;
typedef pair<ll, ll> PII;
const int inf = 0x3f3f3f3f, mod = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
//const int N = 1e5 + 5, M = 2e5 + 5

const int N = 1e5 + 5;
ll n, m, k, a[N];

struct P//存线段，k为-1、1
{
    int x, y1, y2, k;
    bool operator < (const P& t)const
    {
        return x < t.x;
    }
}seg[2 * N];//每个矩阵需要存两个线段

vector<ll>ha;//离散化
int find(double y)
{
    return lower_bound(ha.begin(), ha.end(), y) - ha.begin();
}

struct TR//线段树
{
    int l, r;
    ll cnt;//区间被覆盖几次
    ll len;//区间的长度
}tr[8 * N];

void pushup(int u)
{
    if (tr[u].cnt)tr[u].len = ha[tr[u].r + 1] - ha[tr[u].l];//区间被覆盖，计算长度
    else if (tr[u].l != tr[u].r)tr[u].len = tr[ls].len + tr[rs].len;//区间不是叶节点，长度由子节点计算
    else tr[u].len = 0;
}

void modify(int u, int l, int r, int d)
{
    if (l <= tr[u].l && r >= tr[u].r)
    {
        tr[u].cnt += d;
        pushup(u);
        return;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid)modify(ls, l, r, d);
    if (r > mid)modify(rs, l, r, d);
    pushup(u);
}

void bulid(int u, int l, int r)
{
    tr[u] = { l,r,0,0 };
    if (l == r)return;
    int mid = l + r >> 1;
    bulid(ls, l, mid), bulid(rs, mid + 1, r);
    //此时cnt全是0，不需pushup
}

signed main()
{
    int n; cin >> n;
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        int x1, x2, y1, y2; cin >> x1 >> y1 >> x2 >> y2;//读入点
        seg[j++] = { x1,y1,y2,1 };
        seg[j++] = { x2,y1,y2,-1 };
        ha.pb(y1), ha.pb(y2);//用于离散化
    }
    sort(seg, seg + j);
    sort(ha.begin(), ha.end());
    ha.erase(unique(ha.begin(), ha.end()), ha.end());
    ll ans = 0;

    bulid(1, 0, ha.size() - 2);        
    //例子：假设现在有三个不同的y轴点,分为两个线段
    //y[0] ~ y[1],y[1] ~ y[2];
    //此时ys.size()为3,ys.size() - 2 为 1;
    //此时为 build(1, 0, 1);
    //有两个点0 和 1,线段树中0号点为y[0] ~ y[1],1号点为y[1] ~ y[2];

    for (int i = 0; i < j; i++)
    {
        if (i)ans += (seg[i].x - seg[i - 1].x) * tr[1].len;

        modify(1, find(seg[i].y1), find(seg[i].y2) - 1, seg[i].k);
        //处理一下该线段的信息，是加上该线段还是消去
        //例子：假设进行modify(1，find(10),find(15) - 1,1);
        //      假设find(10) = 0,find(15) = 1;
        //      此时为modify(1, 0, 0, 1);
        //      表示线段树中0号点出现次数加1；
        //      而线段树中0号点刚好为线段(10 ~ 15);
        //      这就是为什么要进行find(seg[i].y2) - 1 的这个-1操作
    }
    cout << ans;
    return 0;
}