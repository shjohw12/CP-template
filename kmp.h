int fail[MAXN];

void init(string t) {
    for (int i = 1, j = 0; i < sz(t); i++) {
        while (j && t[i] != t[j]) {
            j = fail[j - 1];
        }
        if (t[i] == t[j]) {
            fail[i] = ++j;
        }
    }
}

void kmp(string s, string t) {
    for (int i = 0, j = 0; i < sz(s); i++) {
        while (j && s[i] != t[j]) {
            j = fail[j - 1];
        }
        if (t[i] == t[j]) {
            // matching
            if (j == sz(t) - 1) {
                j = fail[j];
            }
            else {
                ++j;
            }
        }
    }
}