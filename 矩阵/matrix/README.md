# matrix
未完成！！
+ 构造传入`(n, m)`,单个`n`为构造出`(n, n)`,也可传入二维vector
+ mul_ident(int n), 传入n构造出(n, n)的单位矩阵
+ inv()，返回<是否可逆，逆矩阵>
+ det(),返回模值
+ 

```cpp
template<typename T> 
struct matrix {
    int n, m;
    std::vector<T> data;
    matrix () : matrix(0, 0) {}
    matrix (int n) : matrix(n, n) {}
    matrix (int n, int m) : n(n), m(m), data(n * m) {}
    matrix (const std::vector<std::vector<T> > &a) : n(a.size()), m(a[0].size()), data(n * m) {
        for (int i = 0; i < n; i++) std::copy(a[i].begin(), a[i].end(), data.begin() + i * m);
    }
    static matrix mul_ident(int n) {
        matrix res(n, n);
        for (int i = 0; i < n; i++) res[i][i] = 1;
        return res;
    }
    auto operator [] (int i) { return data.begin() + i * m; }
    auto operator [] (int i) const { return data.cbegin() + i * m; }
    matrix &operator += (const matrix &rhs) {
        assert(n == rhs.n && m == rhs.m);
        for (int i = 0; i < n * m; i++) data[i] += rhs.data[i];
        return *this;
    }
    matrix &operator -= (const matrix &rhs) {
        assert(n == rhs.n && m == rhs.m);
        for (int i = 0; i < n * m; i++) data[i] -= rhs.data[i];
        return *this;
    }
    matrix operator * (const matrix &rhs) {
        assert(m == rhs.n);
        matrix res(n, rhs.m);
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) for (int k = 0; k < rhs.m; k++)
            res[i][k] += (*this)[i][j] * rhs[j][k];
        return res;
    }
    template<typename int_t> matrix &operator ^= (int_t x) {
        assert(n == m);
        matrix res = mul_ident(n);
        while (x) {
            if (x & 1) res *= *this;
            *this *= *this;
            x >>= 1;
        }
        return (*this = res);
    }
    matrix operator + (const matrix &rhs) const { return matrix(*this) += rhs; }
    matrix operator - (const matrix &rhs) const { return matrix(*this) -= rhs; }
    matrix &operator *= (matrix rhs) & { return (*this = *this * rhs); }
    template<typename int_t> matrix operator ^ (int_t x) const { return matrix(*this) ^= x; }
    bool operator == (const matrix &rhs) const { return m == rhs.m && data == rhs.data; }
    bool operator != (const matrix &rhs) const { return m != rhs.m || data != rhs.data; }
    std::pair<bool, matrix> inv() {
        assert(n == m);
        matrix a = *this;
        std::vector<std::pair<int, int> > swaps;
        for (int i = 0; i < n; i++) {
            int id = -1;
            for (int j = i; j < n; j++) if (a[j][i] != T(0)) { id = j; break; }
            if (id == -1) return {false, matrix()};
            if (id != i) {
                swaps.push_back({id, i});
                for (int j = 0; j < n; j++) std::swap(a[i][j], a[id][j]);
            }
            a[i][i] = T(1) / a[i][i];
            for (int j = 0; j < n; j++) if (j != i) a[i][j] *= a[i][i];
            for (int j = 0; j < n; j++) if (j != i) {
                for (int k = 0; k < n; k++) if (k != i) a[j][k] -= a[j][i] * a[i][k];
                a[j][i] *= -a[i][i];
            }
        }
        for (int i = swaps.size(); i--; ) 
            for (int j = 0; j < n; j++) std::swap(a[j][swaps[i].first], a[j][swaps[i].second]);
        return {true, a};
    }
    T det() const {
        assert(n == m);
        matrix a = *this;
        T res = 1;
        for (int i = 0; i < n; i++) {
            int id = -1;
            for (int j = i; j < n; j++) if (a[j][i] != T(0)) { id = j; break; }
            if (id == -1) return 0;
            if (id != i) {
                res = -res;
                for (int j = i; j < n; j++) std::swap(a[id][j], a[i][j]);
            }
            res *= a[i][i];
            
            T t = T(1) / a[i][i];
            for (int j = i; j < n; j++) a[i][j] *= t;
            for (int j = i + 1; j < n; j++) {
                auto s = a[j][i];
                for (int k = i; k < n; k++) a[j][k] -= a[i][k] * s;
            }
        }
        return res;
    }
    // arbitrary solution, basis for diff
    std::pair<std::vector<T>, std::vector<std::vector<T> > > solve_linear_equations(std::vector<T> rhs) {
        matrix a = *this;
        assert(n == (int) rhs.size());
        int r = 0;
        for (int i = 0; i < m && r < n; i++) {
            int id = -1;
            for (int j = r; j < n; j++) if (a[j][i] != T(0)) { id = j; break; }
            if (id == -1) continue;
            for (int j = i; j < m; j++) std::swap(a[r][j], a[id][j]);
            std::swap(rhs[r], rhs[id]);
            auto t = T(1) / a[r][i];
            for (int j = i; j < m; j++) a[r][j] *= t;
            rhs[r] *= t;
            for (int j = 0; j < n; j++) if (j != r) {
                auto s = a[j][i];
                for (int k = i; k < m; k++) a[j][k] -= a[r][k] * s;
                rhs[j] -= rhs[r] * s;
            }
            r++;
        }
        std::vector<T> sol(m);
        std::vector<bool> primary(m);
        std::vector<int> first_in_row(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) if (a[i][j] != T(0)) { first_in_row[i] = j; break; }
            if (first_in_row[i] == m && rhs[i] != T(0)) return {{}, {}};
            if (first_in_row[i] != m) primary[first_in_row[i]] = true, sol[first_in_row[i]] = rhs[i];
        }
        std::vector<std::vector<T> > basis;
        for (int i = 0; i < m; i++) if (!primary[i]) {
            std::vector<T> cur_base(m);
            cur_base[i] = 1;
            for (int j = 0; j < n; j++) if (a[j][i] != T(0)) cur_base[first_in_row[j]] = -a[j][i];
            basis.push_back(cur_base);
        }
        return {sol, basis};
    }

    template<class C, class F>
    static ll detAnyMod(matrix<C> mat, const ll P, F getval){
        assert(mat.n == mat.m);
        int n=mat.n;
        matrix<ll> a(n);
        for (int i=0; i<n; i++){
            for (int j=0; j<n; j++){
                a[i][j]=getval(mat[i][j]);
            }
        }
        ll res = 1;
        ll w=1;
        for (int i=0; i<n; i++){
            for (int j=i+1; j<n; j++){
                while (a[i][i]!=0){
                    ll div=a[j][i]/a[i][i];
                    for (int k=i; k<n; k++){
                        a[j][k]=(a[j][k]-div*a[i][k]%P+P)%P;
                    }
                    for (int k=0; k<n; k++){
                        std::swap(a[i][k], a[j][k]);
                    }
                    w=-w;
                }
                for (int k=0; k<n; k++){
                    std::swap(a[i][k], a[j][k]);
                }
                w=-w;
            }
        }
        for (int i=0; i<n; i++){
            res=res*a[i][i]%P;
        }
        res=w*res%P;
        return (res+P)%P;
    }
    matrix XOR(){
        matrix a = *this;
        int r = 0, c = 0;
        while (r < n && c < m){
            int mxr = r;
            for (int i = r + 1; i < n; i++){
                if (a[i][c] > a[mxr][c]){
                    mxr = i;
                }
            }
            if (mxr != r){
                for (int j = c; j < m; j++){
                    std::swap(a[r][j], a[mxr][j]);
                }
            }
            if (a[r][c] == 0){
                c++;
                continue;
            }

            for (int i = 0; i < n; i++){
                if (i == r) continue;
                if (a[i][c] == 1){
                    for (int j = c; j < m; j++){
                        a[i][j] ^= a[r][j];
                    }
                }
            }
            r++, c++;
        }
        return a;
    }
};
```