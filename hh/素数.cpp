const int N = 1e5 + 5;
int pr[N], cnt, fac[N];//fac��¼��С������

//����ɸ
void get_prmie(int n)//��Ҫ����������N����Խ�����
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