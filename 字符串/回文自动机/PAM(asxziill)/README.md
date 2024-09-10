# 回文自动机
# PAM 
0奇根，1偶根
+ add加入字符,offset字符基底。返回是否新建节点
每个节点:
+ len该点代表回文串长度
+ link后缀链接
+ cnt该点后缀有多少回文串
+ next子节点
+ suff上次插入字符所在节点的编号
```C++
struct PAM {
    static constexpr int ALPHABET_SIZE = 28;
    struct Node {
        int len;
        int link;
        int cnt;
        std::array<int, ALPHABET_SIZE> next;
        Node() : len{}, link{}, cnt{}, next{} {}
    };
    std::vector<Node> t;
    int suff;
    std::string s;
    PAM() {
        init();
    }
    void init() {
        t.assign(2, Node());
        t[0].len = -1;
        suff = 1;
        s.clear();
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
     
    bool add(char c, char offset = 'a') {
        int pos = s.size();
        s += c;
        int let = c - offset;
        int cur = suff, curlen = 0;
 
        while (true) {
            curlen = t[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos])
                break;  
            cur = t[cur].link;
        }       
        if (t[cur].next[let]) {  
            suff = t[cur].next[let];
            return false;
        }
         
        int num = newNode();
        suff = num;
        t[num].len = t[cur].len + 2;
        t[cur].next[let] = num;
 
        if (t[num].len == 1) {
            t[num].link = 1;
            t[num].cnt = 1;
            return true;
        }
 
        while (true) {
            cur = t[cur].link;
            curlen = t[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
                t[num].link = t[cur].next[let];
                break;
            }       
        }           
 
        t[num].cnt = 1 + t[t[num].link].cnt;
 
        return true;
    }
};
```

例题：[P5496](P5496.md)