#include <bits/stdc++.h>

using namespace std;

// 模数有意默认为 0，迫使自己按题目设置模数
const int P = 0;
using vi = vector<int>;
using vvi = vector<vi>;

// assert 部分可以删除，对矩阵格式做隐式保证
vvi operator*(const vvi& lhs, const vvi& rhs) {
    assert(!lhs.empty() && !rhs.empty());
    int n = lhs.size();
    int K = lhs[0].size();
    int m = rhs[0].size();
    assert((int)rhs.size() == K);

    vvi res(n, vi(m, 0));
    for (int i = 0; i < n; ++i) {
        assert((int)lhs[i].size() == K);
        for (int k = 0; k < K; ++k) {
            for (int j = 0; j < m; ++j) {
                res[i][j] = (res[i][j] + 1LL * lhs[i][k] * rhs[k][j]) % P;
            }
        }
    }
    return res;
}

vvi power(vvi x, long long y) {
    assert(!x.empty());
    int n = x.size();
    assert((int)x[0].size() == n);

    vvi res(n, vi(n, 0));
    for (int i = 0; i < n; ++i) {
        res[i][i] = 1;
    }

    while (y > 0) {
        if (y & 1)
            res = res * x;
        x = x * x;
        y >>= 1;
    }
    return res;
}

// Luogu P3390
void solve() {
    int n;
    long long k;
    cin >> n >> k;
    vvi a(n);
    for (vi& i : a) {
        i.assign(n, 0);
        for (int& j : i)
            cin >> j;
    }
    a = power(a, k);
    for (vi& i : a) {
        for (int& j : i)
            cout << j << " ";
        cout << endl;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
