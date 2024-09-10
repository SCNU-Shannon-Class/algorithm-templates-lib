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
using namespace std;

#define pb push_back
#define x first
#define y second
#define lowbit(x) x&(~x)
#define T_T 0
#define endl "\n"
typedef long long ll;
typedef pair<int, int> PII;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int N = 5e4 + 5, M = 6e3 + 5;
int n, m, k;
int dfn[N], low[N], tt, stk[N], id[N], cnt, si[N], ts;
bool instk[N];
vector<int>g[N];

void tarjan(int u)//缩点
{
	dfn[u] = low[u] = ++ts;
	stk[++tt] = u;
	instk[u] = 1;
	for (int i = 0; i < g[u].size(); i++)
	{
		int j = g[u][i];
		if (!dfn[j])
		{
			tarjan(j);
			low[u] = min(low[u], low[j]);
		}
		else if (instk[j])low[u] = min(low[u], dfn[j]);
	}
	if (low[u] == dfn[u])
	{
		++cnt;
		int v;
		do
		{
			v = stk[tt--];
			instk[v] = 0;
			id[v] = cnt;
			si[cnt]++;
		} while (v != u);
	}
}


//tarjan求割点
// 割点需满足low[v]>=dfn[u],表示子节点v不能回到u的祖宗节点，再分两种情况：
// (1)点u不是根节点，则u是割点
// (2)点u是根节点，则u的子节点大于2个，才是割点
vector<int>ans;
void tarjan(int u, int root)//root是根节点
{
	low[u] = dfn[u] = ++ts;
	int child = 0;//根节点的子节点个数
	for (int i = 0; i < g[u].size(); i++)
	{
		int v = g[u][i];
		if (!dfn[v])
		{
			tarjan(v, root);
			low[u] = min(low[u], low[v]);
			if (u == root)child++;
			if (low[v] >= dfn[u] && u != root)ans.pb(u);//情况(1)
		}
		else low[u] = min(low[u], dfn[v]);
	}
	if (u == root && child >= 2)ans.pb(u);//特判情况(2)
}