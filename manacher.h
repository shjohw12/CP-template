int ma[MAXN]; // ma[i] = s[i-k .. i+k]가 palindrome인 최대 k

void init(string s) {
    int n = sz(s);
    for (int i = 1, r = 0, p = 0; i < n; i++) {
        if (i <= r) {
            ma[i] = min(ma[2 * p - i], r - i);
        }
        while (i - ma[i] - 1 >= 0 && i + ma[i] + 1 < n && s[i - ma[i] - 1] == s[i + ma[i] + 1]) {
            ++ma[i];
        }
        if (r < i + ma[i]) {
            r = i + ma[i], p = i;
        }
    }
}