# KMP
$对字符串s返回数组f,f_i代表[1, i](前i个字符)最长相等前后缀(最长border)(即f_i\rightarrow s_{i-1})$
```C++
std::vector<int> KMP(std::string s) {
    int n = s.size();
    std::vector<int> f(n + 1);
    for (int i = 1, j = 0; i < n; i++) {
        while (j && s[i] != s[j]) {
            j = f[j];
        }
        j += (s[i] == s[j]);
        f[i + 1] = j;
    }
    return f;
}
```

例题：[P3375](P3375.md)