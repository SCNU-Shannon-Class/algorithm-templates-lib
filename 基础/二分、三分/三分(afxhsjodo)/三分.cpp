#include"head.h"

const double eps = 1e-6;
void devide3()//实数三分，P3382
{
    int n; cin >> n;
    double l, r; cin >> l >> r;
    for (int i = 0; i <= n; i++)cin >> a[i];
    auto f = [&](double x)
        {
            double s = 0;
            double t = 1;
            for (int i = n; i >= 0; i--)
            {
                s += t * a[i];
                t *= x;
            }
            return s;
        };
    while (r - l > eps)
    {
        double k = (r - l) / 3.0;
        double mid1 = l + k, mid2 = r - k;
        if (f(mid1) > f(mid2))r = mid2;//这是上凸函数的写法，下凸则把if和else的执行反过来
        else l = mid1;
    }
    cout << l << endl;
}

void devide3()//整数三分
{
    auto f = [&](int x)
        {
            return 1;
        };
    int l = 1, r = n;
    while (r - l > 2)
    {
        int mid1 = l + (r - l) / 3, mid2 = r - (r - l) / 3;
        if (f(mid1) > f(mid2))r = mid2;
        else l = mid1;
    }
}