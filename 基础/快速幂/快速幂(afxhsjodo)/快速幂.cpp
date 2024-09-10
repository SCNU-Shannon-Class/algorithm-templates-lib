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
typedef long long ll;
typedef pair<int, int> PII;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int N = 1e5 + 5, M = 6e3 + 5;
int n, m, mod;

int b[105][105];
int a[105][105];
void mul(int b[105][105], int a[105][105])//æÿ’Û≥À
{
	int c[105][105] = { 0 };
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
			{
				c[i][j] = (c[i][j] + b[i][k] * a[k][j]) % mod;
			}
	//memcpy(b, c, sizeof b);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			b[i][j] = c[i][j];
}

void qs(int a[105][105], int u)//æÿ’ÛøÏÀŸ√›
{
	for (int i = 0; i < n; i++)b[i][i] = 1;
	while (u)
	{
		if (u & 1)mul(b, a);
		mul(a, a);
		u >>= 1;
	}
}

int qmi(int m, int k, int p)//øÏÀŸ√›
{
    int res = 1 % p, t = m;
    while (k)
    {
        if (k & 1) res = res * t % p;
        t = t * t % p;
        k >>= 1;
    }
    return res;
}

