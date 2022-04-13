int z[MAXN]; // z[i] = s[i..]의 prefix와 s의 prefix가 일치하는 최대 길이

void init(string s) {
    int n = sz(s);
    for (int i = 1, r = 0, l = 0; i < n; i++) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[i + z[i]] == s[z[i]]) {
            ++z[i];
        }
        if (r < i + z[i] - 1) {
            r = i + z[i] - 1, l = i;
        }
    }
}