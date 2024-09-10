#include<iostream>
#include<vector>
#include<map>
#include<math.h>
#include<cmath>
#include<cstring>
#include<iomanip>
#include<queue>
#include<algorithm>
#include<stack>
#include<set>
#include<unordered_map>
#include<unordered_set>
using namespace std;

#define pb push_back
#define x first
#define y second
#define lowbit(x) x&(~x)
#define T_T 0
#define endl "\n"
#define ls u<<1
#define rs u<<1|1
//#define int ll
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> PII;
const int inf = 0x3f3f3f3f3f3f3f3f;
const ll INF = 0x3f3f3f3f;
const int N = 2e6 + 5, M = 6e3 + 5;
int n, m, q, k;
ll a[N];

//此题要在一个动态区间内找中位数，即每次加进一个数，弹出n个数，输出中位数

signed main()
{
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int T; cin >> T;
	while (T--)
	{
		int n; cin >> n >> k;
		for (int i = 1; i <= n; i++)cin >> a[i];
		for (int i = 1; i <= n; i++)a[i] -= i;

		multiset<ll>s1, s2;
		//s1存比中位数小的数，s2第一个数为中位数
		//若s2为空，优先放入s2
		//

		ll sum1 = 0, sum2 = 0, ans = 0;
		int l = 1, r = 1;
		auto balance = [&]() -> void//平衡操作，确保s2>=s1，这样s2中的第一个才是中位数
			{
				if (s2.size() > s1.size() + 1)//s2大了，s2中取出第一个放入s1
				{
					ll t = *s2.begin();
					s1.insert(t);
					sum1 += t;
					sum2 -= t;
					s2.erase(s2.begin());
				}
				else if (s1.size() > s2.size())//s1大了，从s1取出最后一个放入s2
				{
					ll t = *s1.rbegin();
					s2.insert(t);
					sum1 -= t;
					sum2 += t;
					s1.erase(prev(s1.end()));
				}
			};
		auto insert = [&](ll x)->void//插入操作，优先放入s2，比s2第一个大的放入s2，小的放入s1
			{
				if (s2.empty())s2.insert(x), sum2 += x;
				else
				{
					ll t = *s2.begin();
					if (x >= t)
					{
						s2.insert(x);
						sum2 += x;
					}
					else
					{
						s1.insert(x);
						sum1 += x;
					}
				}
				balance();
			};
		auto erase = [&](ll x)-> void//取出操作
			{
				if (s1.find(x) != s1.end())s1.erase(s1.find(x)), sum1 -= x;//在s1中找到，则从s1取出
				else s2.erase(s2.find(x)), sum2 -= x;//s1中没找到,说明x在s2中，从s2取出
				balance();
			};
		auto query = [&]()->ll//查询操作
			{
				int si = s1.size() + s2.size();
				if (si & 1)return *s2.begin();//共有奇数个数，则s2第一个为中位数
				else return (*s1.rbegin() + *s2.begin()) / 2;//偶数个数，中位数为s1最后一个和s2第一个的平均值
			};
		auto ques = [&]() -> ll
			{
				ll mid = query();
				ll ned = mid * s1.size() - sum1 + sum2 - mid * s2.size();
				if (ned > k) return false;
				else return true;
			};
		for (l = 1, r = 1; r <= n; r++)
		{
			insert(a[r]);
			while (l <= r && !ques())
			{
				erase(a[l]);
				l++;
			}
			ll si = s1.size() + s2.size();
			ans = max(ans, si);
		}
		cout << ans << "\n";
	}
	return 0;
}