#include"head.h"

istream& operator>>(istream& is, i128& n) 
{
	string s; is >> s;
	n = 0;
	for (char i : s) n = n * 10 + i - '0';
	return is;
}
ostream& operator<<(ostream& os, i128 n) 
{
	string s;
	do
	{
		s += '0' + n % 10;
		n /= 10;
	}while (n);
	reverse(s.begin(), s.end());
	return os << s;
}
ll sqr(ll n)
{
	ll res = sqrt(n);
	while ((res + 1) * (res + 1) <= n)res++;
	while (res * res > n)res--;
	return res;
}
