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
    for (int i = x+1; i <= N; i += lowbit(i))tr[i] += c;//注意是i<=N,不是i<=n，x+1是为了防止x=0的情况，x=0时会死循环
}
int sum(int x)
{
    int res = 0;
    for (int i = x+1; i; i -= lowbit(i))res += tr[i];
    return res;
}

void add1(int x, int c)//树状数组求LIS,两个函数中都只需把+=改成max
{
    for (int i = x+1; i <= N; i += lowbit(i))tr[i] = max(tr[i], c);  
}
int sum1(int x)//树状数组求LIS
{
    int res = 0;
    for (int i = x+1; i; i -= lowbit(i))res = max(res, tr[i]);
    return res;
}
/*
树状LIS的main函数内：
/for (int i = 1; i <= n; i++)
{
    f[i] = sum(a[i]) + 1;//单调降写法：a[i]->N-a[i]+1,下面的add也一样
    add(a[i], f[i]);
}
*/


int d[N];//求区间最大值
void add(int x, int c)
{
    d[x+1] = c;
    for (int i = x+1; i <= N; i += lowbit(i))tr[i] = max(tr[i], c);
}
int query(int x, int y)
{
    int res = 0;
    x++,y++;
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
