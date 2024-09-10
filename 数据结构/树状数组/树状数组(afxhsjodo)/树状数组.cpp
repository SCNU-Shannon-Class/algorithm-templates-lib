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
#define lowbit(x) (x&(-x))
const int N = 32005;
int tr[N];

void add(int x, int c)
{
    for (int i = x+1; i <= N; i += lowbit(i))tr[i] += c;//ע����i<=N,����i<=n��x+1��Ϊ�˷�ֹx=0�������x=0ʱ����ѭ��
}
int sum(int x)
{
    int res = 0;
    for (int i = x+1; i; i -= lowbit(i))res += tr[i];
    return res;
}

void add1(int x, int c)//��״������LIS,���������ж�ֻ���+=�ĳ�max
{
    for (int i = x+1; i <= N; i += lowbit(i))tr[i] = max(tr[i], c);  
}
int sum1(int x)//��״������LIS
{
    int res = 0;
    for (int i = x+1; i; i -= lowbit(i))res = max(res, tr[i]);
    return res;
}
/*
��״LIS��main�����ڣ�
/for (int i = 1; i <= n; i++)
{
    f[i] = sum(a[i]) + 1;//������д����a[i]->N-a[i]+1,�����addҲһ��
    add(a[i], f[i]);
}
*/


int n, m;//���������ֵ
int d[N];
void add(int x, int c)
{
    d[x] = c;
    for (int i = x+1; i <= n; i += lowbit(i))tr[i] = max(tr[i], c);
}
int query(int x, int y)
{
    int res = 0;
    while (x <= y)
    {
        while (y - x >= lowbit(y))
        {
            res = max(res, tr[y]);
            y -= lowbit(y);
        }
        res = max(res, d[y]);
        y--;
    }
    return res;
}