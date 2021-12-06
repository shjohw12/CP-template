int fail[MAXN];

for (int i = 1, j = 0; i < sz(t); i++) {
    while (j && t[i] != t[j]) {
        j = fail[j - 1];
    }
    if (t[i] == t[j]) {
        ++j;
    }
    fail[i] = j;
}

for (int i = 0, j = 0; i < sz(s); i++) {
    while (j && s[i] != t[j]) {
        j = fail[j - 1];
    }
    if (s[i] == t[j]) {
        ++j;
    }
    // matching
    if (j == sz(t)) {
        j = fail[j - 1];
    }
}