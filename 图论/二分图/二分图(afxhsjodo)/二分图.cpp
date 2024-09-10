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
const int inf = 0x3f3f3f3f3f3f3f3f;
const ll INF = 0x3f3f3f3f;
const int N = 1e5 + 5, M = 6e3 + 5;
int n, m, q, k;
vector<int>g[N];

//染色法判二分图，复杂度O(n+m),n是点数,m是边数
int color[N];// 表示每个点的颜色，0表示未染色，1表示白色，2表示黑色
bool dfs(int u, int c)
{
	color[u] = c;
	for (int i = 0; i < g[u].size(); i++)
	{
		int v = g[u][i];
		if (color[v] == 0)
		{
			if (!dfs(v, 3 - c))return 0;
		}
		else if (color[v] == c)return 0;
	}
	return 1;
}
bool check()
{
	memset(color, 0, sizeof color);
	bool flag = true;
	for (int i = 1; i <= n; i++)
		if (color[i] == 0)
			if (!dfs(i, 1))
			{
				flag = false;
				break;
			}
	return flag;
}



//二分图中，若最大匹配=m，则最小点覆盖=m，最大独立集=n-m
//最大独立集：选出最多的点，点与点之间没有边
bool st[N];
int match[N];
bool find(int x)//匈牙利算法求最大匹配,复杂度O(nm),n是点数,m是边数
{
	for (int i = 0; i < g[x].size(); i++)
	{
		int j = g[x][i];
		if (!st[j])
		{
			st[j] = 1;
			if (match[j] == 0 || find(match[j]))
			{
				match[j] = x;
				return 1;
			}
		}
	}
	return 0;
}
//main函数内部：
/*
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		memset(st, 0, sizeof st);
		ans += find(i);
	}
	cout << ans;
*/