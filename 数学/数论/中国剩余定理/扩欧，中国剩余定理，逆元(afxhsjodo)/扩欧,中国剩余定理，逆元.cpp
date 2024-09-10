#include<iostream>
#include<vector>
#include<map>
#include<math.h>
#include<cmath>
#include<cstring>
#include<iomanip>
#include<queue>
#include<algorithm>
#include<stack>
#include<set>
#include<bitset>
#include<unordered_map>
#include<unordered_set>
using namespace std;

#define pb push_back
#define x first
#define y second
#define lowbit(x) x&(~x)
#define T_T 0
#define endl "\n"
#define ls u<<1
#define rs u<<1|1
#define i128 __int128
typedef long long ll;
typedef ll LL;
typedef unsigned long long ull;

//void pf(i128 x) { if (x < 0) putchar('-'), x = -x; if (x > 9)pf(x / 10); putchar(x % 10 + 48); }
int T = 1;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int N = 2e5 + 5;
//#define int ll
typedef pair<int, int> PII;

ll exgcd(ll a, ll b, ll& x, ll& y)
{
    if (!b)
    {
        x = 1; y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

ll inver(ll a, ll m)//求逆元
{
	ll x, y;
	exgcd(a, m, x, y);
	return (x % m + m) % m;
}

//中国剩余定理，P1475
ll n, m, k, q;
ll a[N], b[N];
int gcd(int a, int b){return b ? gcd(b, a % b) : a;}

void solve()
{
	cin >> n;
	ll m = 1;
	ll ans = 0;
	for (int i = 0; i < n; i++)cin >> a[i] >> b[i], m *= a[i];
	for (int i = 0; i < n; i++)
	{
		ll mi = m / gcd(m, a[i]);
		ll t, x;
		exgcd(mi, a[i], t, x);
		ans = (ans + b[i] * t * mi) % m;
	}
	cout << (ans % m + m) % m;
}
