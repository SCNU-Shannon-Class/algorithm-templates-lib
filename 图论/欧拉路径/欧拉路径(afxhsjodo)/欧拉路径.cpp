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
//#define int ll
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> PII;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int N = 2e5 + 5, M = 6e3 + 5;
#define int ll
int n, m, q, k;
vector<PII>g[N];//x是边的终点，y是边的序号
int du[N];//点的度数
bool st[N];//边的判重
int b[N];//枚举的起点，表示删掉了前面的边

//P7771
vector<int>ans;
void dfs(int u)//有向图的欧拉路径
{
	for (int i = b[u]; i < g[u].size(); i = b[u])
	{
		if (st[g[u][i].y])
		{
			continue;
		}
		b[u] = i + 1;
		st[g[u][i].y] = 1;
		int v = g[u][i].x;
		dfs(v);
	}
	ans.pb(u);
}

void solve()
{
	cin >> n >> m;
	int cnt = 0;
	for (int i = 0; i < m; i++)
	{
		int u, v; cin >> u >> v;
		g[u].pb({ v,++cnt });
		du[u]++, du[v]--;
	}
	for (int i = 1; i <= n; i++)sort(g[i].begin(), g[i].end());//排序，使输出是字典序
	int beg = 1, t = 0;//beg是dfs的起点，t是奇点的数量
	for (int i = n; i >= 1; i--)//倒序，使beg是小的点，因为要按字典序
	{
		if (du[i] & 1)beg = i, t++;//奇点为起点
	}
	if (t > 2)cout << "No";
	else
	{
		dfs(beg);
		reverse(ans.begin(), ans.end());
		for (int i = 0; i < ans.size(); i++)cout << ans[i] << " ";
	}
}

signed main()
{
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int T;
	T = 1;
	while (T--)
	{
		solve();
	}
	return 0;
}