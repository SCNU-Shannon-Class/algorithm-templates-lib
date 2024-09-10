#include<iostream>
#include<vector>
#include<map>
#include<math.h>
#include<cmath>
#include<cstring>
#include<iomanip>
#include<queue>
#include<stack>
using namespace std;

#define pb push_back
#define x first
#define y second
#define lowbit(x) x&(~x)
#define T_T 0
#define endl "\n"
typedef long long ll;
typedef pair<int, int> PII;
const int N = 5e5 + 5, M = 6e3 + 5;
int n, m, s;
vector<int>g[N];
int depth[N];
int fa[N][22];

//luogu3379

void bfs(int root)//传入根节点,预处理fa和depth数组
{
	memset(depth, 0x3f, sizeof depth);
	depth[0] = 0, depth[root] = 1;
	queue<int>q;
	q.push(root);
	while (q.size())
	{
		int t = q.front();
		q.pop();
		for (int i = 0; i < g[t].size(); i++)
		{
			int j = g[t][i];
			if (depth[j] > depth[t] + 1)
			{
				depth[j] = depth[t] + 1;
				q.push(j);
				fa[j][0] = t;
				for (int k = 1; k <= 21; k++)fa[j][k] = fa[fa[j][k - 1]][k - 1];
			}
		}
	}
}

int lca(int a, int b)//倍增法
{
	if (depth[a] < depth[b])swap(a, b);
	for (int i = 21; i >= 0; i--)
		if (depth[fa[a][i]] >= depth[b])a = fa[a][i];
	if (a == b)return a;
	for (int i = 21; i >= 0; i--)
		if (fa[a][i] != fa[b][i])
		{
			a = fa[a][i];
			b = fa[b][i];
		}
	return fa[a][0];
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m >> s;
	for (int i = 0; i < n - 1; i++)
	{
		int u, v; cin >> u >> v;
		if (u != v)g[v].pb(u), g[u].pb(v);
	}
	bfs(s);
	for (int i = 0; i < m; i++)
	{
		int u, v; cin >> u >> v;
		if (u == v)cout << u << endl;
		else cout << lca(u, v) << endl;
	}
	return T_T;
}


//下面是tarjan算法
vector<PII>query[N];
int ans[N];
int st[N];
int p[N];
int find(int x)
{
	if (p[x] != x)p[x] = find(p[x]);
	return p[x];
}
void tarjan(int u)
{
	st[u] = 1;
	for (int i = 0; i < g[u].size(); i++)
	{
		int j = g[u][i];
		if (!st[j])
		{
			tarjan(j);
			p[j] = u;
		}
	}
	for (auto i : query[u])
	{
		int t = i.x, id = i.y;
		if (st[t] == 2)ans[id] = find(t);
	}
	st[u] = 2;
}