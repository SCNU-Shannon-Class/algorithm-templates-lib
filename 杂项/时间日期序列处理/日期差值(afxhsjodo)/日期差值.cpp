const int month[]{ 0,31,28,31,30,31,30,31,31,30,31,30,31 };

bool is_leap(int y)//判断闰年
{
    return y % 4 == 0 && y % 100 != 0 || y % 400 == 0;
}

int get_day(int y, int m)//求某个月的天数
{
    if (m == 2)return 28 + is_leap(y);
    else return month[m];
}

int val(int year, int month, int day)//计算到0001年有多少天
{
    int res = 0;
    for (int i = 1; i < year; i++)res += 365 + is_leap(i); // 距离1年有多少年
    for (int i = 1; i < month; i++)res += get_day(year, i); // 本年的前面天数   
    res += day; // 本年本月的所有天数
    return res;
}

void nextday(int& y, int& m, int& d)//枚举每一天
{
    d++;
    if (d > get_day(y, m))d = 1, m++;
    if (m > 12)m = 1,y++;
}