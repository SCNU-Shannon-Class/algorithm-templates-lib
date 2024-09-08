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
vector<PII>g[N];//x�Ǳߵ��յ㣬y�Ǳߵ����
int du[N];//��Ķ���
bool st[N];//�ߵ�����
int b[N];//ö�ٵ���㣬��ʾɾ����ǰ��ı�

//P7771
vector<int>ans;
void dfs(int u)//����ͼ��ŷ��·��
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
	for (int i = 1; i <= n; i++)sort(g[i].begin(), g[i].end());//����ʹ������ֵ���
	int beg = 1, t = 0;//beg��dfs����㣬t����������
	for (int i = n; i >= 1; i--)//����ʹbeg��С�ĵ㣬��ΪҪ���ֵ���
	{
		if (du[i] & 1)beg = i, t++;//���Ϊ���
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