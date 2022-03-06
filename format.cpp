// #pragma GCC optimize("Ofast")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#include<bits/stdc++.h>
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
ostream &operator<<(ostream &os, tuple<auto, auto, auto> t) {
    return os << '(' << get<0>(t) << ' ' << get<1>(t) << ' ' << get<2>(t) << ')';
}
ostream &operator<<(ostream &os, tuple<auto, auto, auto, auto> t) {
    return os << '(' << get<0>(t) << ' ' << get<1>(t) << ' ' << get<2>(t) << ' ' << get<3>(t) << ')';
}
ostream &operator<<(ostream &os, tuple<auto, auto, auto, auto, auto> t) {
    return os << '(' << get<0>(t) << ' ' << get<1>(t) << ' ' << get<2>(t) << ' ' << get<3>(t) << ' ' << get<4>(t) << ')';
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





















signed main() {
#ifdef LOCAL
    freopen("debug.txt", "w", stderr);
    freopen("output.txt", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(20);





























    return 0;
}