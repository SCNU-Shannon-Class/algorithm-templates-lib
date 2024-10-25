const int N = 1e5 + 5;
int pr[N], cnt, fac[N];//fac记录最小质因子

//线性筛
void get_prime(int n)//不要在这里输入N，有越界风险
{
	for (int i = 2; i <= n; i++)
	{
		if (!fac[i])pr[cnt++] = i, fac[i] = i;
		for (int j = 0;j < cnt; j++)
		{
			if (pr[j] >= n / i)break;
			fac[pr[j] * i] = pr[j];
			if (i % pr[j] == 0)break;
		}
	}
}
