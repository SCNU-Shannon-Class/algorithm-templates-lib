#include"head.h"
//P3372,区间查+区间改
int a[N];
struct ST
{
    int l, r;
    ll sum;
    ll lz;
    ll cnt;
}tr[4 * N];
void pushup(int u)
{
    tr[u].sum = tr[ls].sum + tr[rs].sum;
}
void calc(ST& t, ll a)
{
    t.sum += a;
}
void pushdown(int u)
{
    tr[ls].lz += tr[u].lz;
    tr[rs].lz += tr[u].lz;
    tr[ls].sum += tr[u].lz * (tr[ls].r - tr[ls].l + 1);
    tr[rs].sum += tr[u].lz * (tr[rs].r - tr[rs].l + 1);
    tr[u].lz = 0;
}
void build(int u, int l, int r)
{
    tr[u] = { l,r,a[l],0,1 };
    if (l == r)return;
    ll mid = l + r >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
    pushup(u);
}
ll query(int u, int l, int r)
{
    if (tr[u].l >= l && tr[u].r <= r)return tr[u].sum;
    ll mid = tr[u].l + tr[u].r >> 1;
    pushdown(u);
    ll s = 0;
    if (l <= mid)
        s = query(ls, l, r) + s;
    if (r > mid)
        s = query(rs, l, r) + s;
    return s;
}
void change(int u, int l, int r, ll a)
{
    if (l > tr[u].r || r < tr[u].l)return;
    if (l <= tr[u].l && r >= tr[u].r)
    {
        tr[u].lz += a;
        tr[u].sum += a * (tr[u].r - tr[u].l + 1);
        return;
    }
    pushdown(u);
    change(ls, l, r, a);
    change(rs, l, r, a);
    pushup(u);
}

void solve()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)cin >> a[i];
    build(1, 1, n);
    for (int i = 1; i <= m; i++)
    {
        int t, x, y, k; cin >> t;
        if (t == 1)
        {
            cin >> x >> y >> k;
            change(1, x, y, k);
        }
        else
        {
            cin >> x >> y;
            cout << query(1, x, y) << endl;
        }
    }
}
/*

*/
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    //cin >> T;
    while (T--)solve();
    return 0;
}