// #pragma GCC optimize("Ofast")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#include<bits/stdc++.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<unistd.h>
// #include<ext/pb_ds/assoc_container.hpp>
// #include<ext/pb_ds/tree_policy.hpp>
// #include<ext/rope>
#define int ll
#define sz(x) int((x).size())
#define all(x) (x).begin(),(x).end()
using namespace std;
using ll = long long;
using pi = pair<int, int>;
const int inf = 0x3f3f3f3f3f3f3f3f;
const int minf = 0xc0c0c0c0c0c0c0c0;

#ifdef LOCAL
ostream &operator<<(ostream &os, pair<auto, auto> p) {
    return os << '(' << p.first << ' ' << p.second << ')';
}
template<typename T, size_t N> struct tuplePrinter {
    static ostream &print(ostream &os, T t) { return tuplePrinter<T, N - 1>::print(os, t) << ' ' << get<N - 1>(t); }
};
template<typename T> struct tuplePrinter<T, 1> {
    static ostream &print(ostream &os, T t) { return os << get<0>(t); }
};
template<typename... args> ostream &print_tuple(ostream &os, tuple<args...> t) {
    return tuplePrinter<decltype(t), sizeof...(args)>::print(os << "(", t) << ")";
}
template<typename ...args> ostream &operator<<(ostream &os, const tuple<args...> t) {
    return print_tuple(os, t);
}
ostream &operator<<(ostream &os, priority_queue<auto, auto, auto> v) {
    bool flag = false;
    os << '[';
    while (sz(v)) {
        if (flag) {
            os << ' ';
        }
        flag = true;
        os << v.top();
        v.pop();
    }
    os << ']';
    return os;
}
template<typename C, typename T = typename enable_if<!is_same<C, string>::value, typename C::value_type>::type>
ostream &operator<<(ostream &os, C container) {
    os << '[';
    bool flag = false;
    for (auto x : container) {
        if (flag) {
            os << ' ';
        }
        flag = true;
        os << x;
    }
    return os << ']';
}
void debug_out() { cerr << endl; }
template<typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cerr << H;
    if (sizeof...(T)) {
        cerr << ", ";
    }
    debug_out(T...);
}
#define debug(...) cerr << #__VA_ARGS__ << " = ", debug_out(__VA_ARGS__)
#else
#define debug(...) 0xF
#endif

const char dgt[] = "00010203040506070809101112131415161718192021222324252627282930313233343536373839404142434445464748495051525354555657585960616263646566676869707172737475767778798081828384858687888990919293949596979899";
const int BUF_SZ = 1 << 20;
const char c15 = char(15), c16 = char(16);
char readbuf[BUF_SZ], writebuf[BUF_SZ];
char *INPUT = readbuf, *OUTPUT = writebuf;

// mmap
inline void get(signed &n) {
    n = 0;
    bool flag = false;
    if (*INPUT == '-') {
        flag = true;
        ++INPUT;
    }
    for (char i = *INPUT++; i & c16; n = (n << 1) + (n << 3) + (i & c15), i = *INPUT++);
    if (flag) {
        n = -n;
    }
}

inline void get(ll &n) {
    n = 0;
    bool flag = false;
    if (*INPUT == '-') {
        flag = true;
        ++INPUT;
    }
    for (char i = *INPUT++; i & c16; n = (n << 1) + (n << 3) + (i & c15), i = *INPUT++);
    if (flag) {
        n = -n;
    }
}

// // read
// inline void get(signed &n) {
//     n = 0;
//     bool flag = false;
//     if (INPUT == readbuf + BUF_SZ) {
//         read(0, INPUT = readbuf, BUF_SZ);
//     }
//     if (*INPUT == '-') {
//         flag = true;
//         ++INPUT;
//     }
//     if (INPUT == readbuf + BUF_SZ) {
//         read(0, INPUT = readbuf, BUF_SZ);
//     }
//     for (char i = *INPUT++; i & c16; n = (n << 1) + (n << 3) + (i & c15), i = *INPUT++) {
//         if (INPUT == readbuf + BUF_SZ) {
//             read(0, INPUT = readbuf, BUF_SZ);
//         }
//     }
//     if (flag) {
//         n = -n;
//     }
// }

// inline void get(ll &n) {
//     n = 0;
//     bool flag = false;
//     if (INPUT == readbuf + BUF_SZ) {
//         read(0, INPUT = readbuf, BUF_SZ);
//     }
//     if (*INPUT == '-') {
//         flag = true;
//         ++INPUT;
//     }
//     if (INPUT == readbuf + BUF_SZ) {
//         read(0, INPUT = readbuf, BUF_SZ);
//     }
//     for (char i = *INPUT++; i & c16; n = (n << 1) + (n << 3) + (i & c15), i = *INPUT++) {
//         if (INPUT == readbuf + BUF_SZ) {
//             read(0, INPUT = readbuf, BUF_SZ);
//         }
//     }
//     if (flag) {
//         n = -n;
//     }
// }

// // fread
// inline void get(signed &n) {
//     n = 0;
//     bool flag = false;
//     if (INPUT == readbuf + BUF_SZ) {
//         fread(readbuf, sizeof(char), BUF_SZ, stdin);
//     }
//     if (*INPUT == '-') {
//         flag = true;
//         ++INPUT;
//     }
//     if (INPUT == readbuf + BUF_SZ) {
//         fread(readbuf, sizeof(char), BUF_SZ, stdin);
//     }
//     for (char i = *INPUT++; i & c16; n = (n << 1) + (n << 3) + (i & c15), i = *INPUT++) {
//         if (INPUT == readbuf + BUF_SZ) {
//             fread(readbuf, sizeof(char), BUF_SZ, stdin);
//         }
//     }
//     if (flag) {
//         n = -n;
//     }
// }

// inline void get(ll &n) {
//     n = 0;
//     bool flag = false;
//     if (INPUT == readbuf + BUF_SZ) {
//         fread(readbuf, sizeof(char), BUF_SZ, stdin);
//     }
//     if (*INPUT == '-') {
//         flag = true;
//         ++INPUT;
//     }
//     if (INPUT == readbuf + BUF_SZ) {
//         fread(readbuf, sizeof(char), BUF_SZ, stdin);
//     }
//     for (char i = *INPUT++; i & c16; n = (n << 1) + (n << 3) + (i & c15), i = *INPUT++) {
//         if (INPUT == readbuf + BUF_SZ) {
//             fread(readbuf, sizeof(char), BUF_SZ, stdin);
//         }
//     }
//     if (flag) {
//         n = -n;
//     }
// }

// write
inline void put(int n) {
    int SZ = OUTPUT - writebuf;
    if (BUF_SZ - SZ < 25) {
        write(1, writebuf, SZ);
        OUTPUT = writebuf;
    }
    if (n == 0) {
        *OUTPUT++ = '0';
        return;
    }
    if (n < 0) {
        *OUTPUT++ = '-';
        n = -n;
    }
    char *tmp = OUTPUT;
    for (int i = (n % 100) << 1; n > 99; n /= 100, i = (n % 100) << 1) {
        *OUTPUT++ = dgt[i | 1];
        *OUTPUT++ = dgt[i];
    }
    if (n > 9) {
        n <<= 1;
        *OUTPUT++ = dgt[n | 1];
        *OUTPUT++ = dgt[n];
    }
    else if (n > 0) {
        *OUTPUT++ = n | 48;
}
    reverse(tmp, OUTPUT);
}

// // fwrite
// inline void put(int n) {
//     int SZ = OUTPUT - writebuf;
//     if (BUF_SZ - SZ < 25) {
//         fwrite(writebuf, sizeof(char), SZ, stdout);
//         OUTPUT = writebuf;
//     }
//     if (n == 0) {
//         *OUTPUT++ = '0';
//         return;
//     }
//     if (n < 0) {
//         *OUTPUT++ = '-';
//         n = -n;
//     }
//     char *tmp = OUTPUT;
//     for (int i = (n % 100) << 1; n > 99; n /= 100, i = (n % 100) << 1) {
//         *OUTPUT++ = dgt[i | 1];
//         *OUTPUT++ = dgt[i];
//     }
//     if (n > 9) {
//         n <<= 1;
//         *OUTPUT++ = dgt[n | 1];
//         *OUTPUT++ = dgt[n];
//     }
//     else if (n > 0) {
//         *OUTPUT++ = n | 48;
//     }
//     reverse(tmp, OUTPUT);
// }





















signed main() {
#ifdef LOCAL
    freopen("debug.txt", "w", stderr);
    freopen("output.txt", "w", stdout);
#endif
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    // cout << fixed << setprecision(20);
    struct stat stt; fstat(0, &stt);
    INPUT = (char *)mmap(0, stt.st_size, PROT_READ, MAP_SHARED, 0, 0);
    // read(0, readbuf, BUF_SZ);
    // fread(readbuf, sizeof(char), BUF_SZ, stdin);











    int TC; get(TC);
    while (TC--) {
        int a, b;
        get(a); get(b);
        put(a + b); *OUTPUT++ = '\n';
    }











    write(1, writebuf, OUTPUT - writebuf);
    // fwrite(writebuf, sizeof(char), OUTPUT - writebuf, stdout);

    return 0;
}