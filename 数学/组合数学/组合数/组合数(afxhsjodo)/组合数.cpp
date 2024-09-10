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
const int N = 1e3 + 5, M = 6e3 + 5;
int n, m, k;
const int N = 1e3 + 5;
int c[N][N];

void init()
{
	for(int i=0;i<N;i++)
		for (int j = 0; j <= i; j++)
		{
			if (!j)c[i][j] = 1;
			else c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
		}
}

void catalan(int n)//卡特兰数,Cal(n)=C(2n,n)/(n+1)=C(2n,n)-C(2n,n-1)
{
	for (int i = 1; i <= 2 * n; i++)
	{
		c[i][0] = c[i][i] = 1;
		for (int j = 1; j < i; j++)
		{
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
		}
	}
	cout<<c[2 * n][n] - c[2 * n][n - 1];
}
/*
py实现:
n>500时，catalan数极大，此时使用的公式是，Cal(n)=(4n-2)/n+1*Cal(n-1)
	n=int(input())
	c=1
	for i in range (1,n+1):
		c=c*(4*i-2)//(i+1)
	print(c)
*/