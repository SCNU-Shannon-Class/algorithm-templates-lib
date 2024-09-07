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

//Ⱦɫ���ж���ͼ�����Ӷ�O(n+m),n�ǵ���,m�Ǳ���
int color[N];// ��ʾÿ�������ɫ��0��ʾδȾɫ��1��ʾ��ɫ��2��ʾ��ɫ
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



//����ͼ�У������ƥ��=m������С�㸲��=m����������=n-m
//����������ѡ�����ĵ㣬�����֮��û�б�
bool st[N];
int match[N];
bool find(int x)//�������㷨�����ƥ��,���Ӷ�O(nm),n�ǵ���,m�Ǳ���
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
//main�����ڲ���
/*
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		memset(st, 0, sizeof st);
		ans += find(i);
	}
	cout << ans;
*/