#include "head.h"

// s[]是长文本，p[]是模式串，n是s的长度，m是p的长度
static const int N = 1e5+5;
int ne[N], n, m;
string s, p;

void kmp()
{
    //求模式串的Next数组：
    for (int i = 2, j = 0; i <= m; i++)
    {
        while (j && p[i] != p[j + 1]) j = ne[j];
        if (p[i] == p[j + 1]) j++;
        ne[i] = j;
    }

    // 匹配
    for (int i = 1, j = 0; i <= n; i++)
    {
        while (j && s[i] != p[j + 1]) j = ne[j];
        if (s[i] == p[j + 1]) j++;
        if (j == m)
        {
            j = ne[j];
            // 匹配成功后的逻辑
        }
    }
}