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
#define nmsl cout<<"\nnmsl\n";//ũó˰��
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

struct P//���߶Σ�kΪ-1��1
{
    int x, y1, y2, k;
    bool operator < (const P& t)const
    {
        return x < t.x;
    }
}seg[2 * N];//ÿ��������Ҫ�������߶�

vector<ll>ha;//��ɢ��
int find(double y)
{
    return lower_bound(ha.begin(), ha.end(), y) - ha.begin();
}

struct TR//�߶���
{
    int l, r;
    ll cnt;//���䱻���Ǽ���
    ll len;//����ĳ���
}tr[8 * N];

void pushup(int u)
{
    if (tr[u].cnt)tr[u].len = ha[tr[u].r + 1] - ha[tr[u].l];//���䱻���ǣ����㳤��
    else if (tr[u].l != tr[u].r)tr[u].len = tr[ls].len + tr[rs].len;//���䲻��Ҷ�ڵ㣬�������ӽڵ����
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
    //��ʱcntȫ��0������pushup
}

signed main()
{
    int n; cin >> n;
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        int x1, x2, y1, y2; cin >> x1 >> y1 >> x2 >> y2;//�����
        seg[j++] = { x1,y1,y2,1 };
        seg[j++] = { x2,y1,y2,-1 };
        ha.pb(y1), ha.pb(y2);//������ɢ��
    }
    sort(seg, seg + j);
    sort(ha.begin(), ha.end());
    ha.erase(unique(ha.begin(), ha.end()), ha.end());
    ll ans = 0;

    bulid(1, 0, ha.size() - 2);        
    //���ӣ�����������������ͬ��y���,��Ϊ�����߶�
    //y[0] ~ y[1],y[1] ~ y[2];
    //��ʱys.size()Ϊ3,ys.size() - 2 Ϊ 1;
    //��ʱΪ build(1, 0, 1);
    //��������0 �� 1,�߶�����0�ŵ�Ϊy[0] ~ y[1],1�ŵ�Ϊy[1] ~ y[2];

    for (int i = 0; i < j; i++)
    {
        if (i)ans += (seg[i].x - seg[i - 1].x) * tr[1].len;

        modify(1, find(seg[i].y1), find(seg[i].y2) - 1, seg[i].k);
        //����һ�¸��߶ε���Ϣ���Ǽ��ϸ��߶λ�����ȥ
        //���ӣ��������modify(1��find(10),find(15) - 1,1);
        //      ����find(10) = 0,find(15) = 1;
        //      ��ʱΪmodify(1, 0, 0, 1);
        //      ��ʾ�߶�����0�ŵ���ִ�����1��
        //      ���߶�����0�ŵ�պ�Ϊ�߶�(10 ~ 15);
        //      �����ΪʲôҪ����find(seg[i].y2) - 1 �����-1����
    }
    cout << ans;
    return 0;
}