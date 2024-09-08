const int month[]{ 0,31,28,31,30,31,30,31,31,30,31,30,31 };

bool is_leap(int y)//�ж�����
{
    return y % 4 == 0 && y % 100 != 0 || y % 400 == 0;
}

int get_day(int y, int m)//��ĳ���µ�����
{
    if (m == 2)return 28 + is_leap(y);
    else return month[m];
}

int val(int year, int month, int day)//���㵽0001���ж�����
{
    int res = 0;
    for (int i = 1; i < year; i++)res += 365 + is_leap(i); // ����1���ж�����
    for (int i = 1; i < month; i++)res += get_day(year, i); // �����ǰ������   
    res += day; // ���걾�µ���������
    return res;
}

void nextday(int& y, int& m, int& d)//ö��ÿһ��
{
    d++;
    if (d > get_day(y, m))d = 1, m++;
    if (m > 12)m = 1,y++;
}