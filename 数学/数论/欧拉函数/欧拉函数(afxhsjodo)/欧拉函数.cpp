int phi(int x)
{
	int res = x;
	for (int i = 2; i <= x / i; i++)
	{
		if (x % i == 0)
		{
			res = res / i * (i - 1);
			while (x % i == 0)x /= i;
		}
	}
	if (x > 1)res / x * (x - 1);
	return res;
}

const int N = 1e5 + 5;
int prime[N], cnt;     // prime[]存储所有素数
int euler[N];           // 存储每个数的欧拉函数
bool st[N];         // st[x]存储x是否被筛掉

void get_euler(int n)//筛法求欧拉函数
{
	euler[1] = 1;
	for(int i = 2;i <= n; i++)
	{
		if (!st[i])
		{
			prime[cnt++] = i;
			euler[i] = i - 1;
		}
		for (int j = 0; prime[j] <= n / i; j++)
		{
			int t = prime[j] * i;
			st[t] = 1;
			if (i % prime[j] == 0)
			{
				euler[t] = euler[i] * prime[j];
				break;
			}
			euler[t] = euler[i] * (prime[j] - 1);
		}
	}
}
