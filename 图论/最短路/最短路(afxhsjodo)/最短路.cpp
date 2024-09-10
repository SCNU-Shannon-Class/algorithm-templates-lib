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

#define x first 
#define y second
typedef pair<int, int> PII;
const int N = 1e5 + 5;
int dist[N];
vector<PII>g[N];
bool st[N];

void dijkstra(int s)
{
	memset(dist, 0x3f, sizeof dist);
	memset(st, 0, sizeof st);
	priority_queue<PII, vector<PII>, greater<PII>>q;
	dist[1] = 0;
	q.push({0,1});
	while (q.size())
	{
		auto t = q.top();
		q.pop();
		if (st[t.y] = 1)continue;
		st[t.y] = 1;
		for (int i = 0; i < g[t.y].size(); i++)
		{
			auto v = g[t.y][i];
			if (dist[v.y] > dist[t.y] + v.x)
			{
				dist[v.y] = dist[t.y] + v.x;
				q.push({ dist[v.y],v.y });
			}
		}
	}
}

void spfa(int s)
{
	memset(dist, 0x3f, sizeof dist);
	memset(st, 0, sizeof st);
	queue<int>q;
	dist[1] = 0;
	st[1] = 0;//可不写
	q.push(1);
	while (q.size())
	{
		int u = q.front();
		q.pop();
		st[u] = 0;
		for (int i = 0; i < g[u].size(); i++)
		{
			auto v = g[u][i];
			if (dist[v.y] > dist[u] + v.x)
			{
				dist[v.y] = dist[u] + v.x;
				if (!st[v.y])q.push(v.y), st[v.y] = 1;
			}
		}
	}
}

int du[N], n;
vector<int>top;
void topsort()
{
	queue<int>q;
	for (int i = 1; i <= n; i++)
		if (!du[i])q.push(i), top.push_back(i);
	while (q.size())
	{
		int u = q.front();
		q.pop();
		for (int i = 0; i < g[u].size(); i++)
		{
			int v = g[u][i].y;
			if (--du[v] == 0)top.push_back(v);
		}
	}
}

//spfa求负环
int cnt[N];
bool spfa()
{
	memset(cnt, 0, sizeof cnt);
	queue<int>q;//tle了可以换成stack试试
	q.push(0);
	dist[0] = 0;
	for (int i = 1; i <= n; i++)q.push(i), st[i] = 1;
	while (q.size())
	{
		int u = q.front();
		q.pop();
		st[u] = 0;
		for (int i = 0; i < g[u].size(); i++)
		{
			auto v = g[u][i];
			if (dist[v.x] > dist[u] + v.y)
			{
				dist[v.x] = dist[u] + v.y;
				cnt[v.x] = cnt[u] + 1;
				if (cnt[v.x] >= n)return 1;//返回1表示有负环
				if (!st[v.x])
				{
					q.push(v.x);
					st[v.x] = 1;
				}
			}
		}
	}
	return 0;//没有负环
}