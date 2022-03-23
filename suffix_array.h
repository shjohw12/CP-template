struct Sa {
    int n;
    vector<int> sa, rnk, rnk_nxt, idx, cnt, lcp;

    Sa(string s) : n(sz(s)), sa(n), rnk(2 * n), rnk_nxt(2 * n), idx(n), cnt(max(n, int(128)) + 1), lcp(n) {
        for (int i = 0; i < n; i++) {
            sa[i] = i;
            rnk[i] = s[i];
        }
        for (int d = 1;; d <<= 1) {
            fill(all(cnt), 0);
            for (int i = 0; i < n; i++) {
                ++cnt[rnk[i + d]];
            }
            for (int i = 1; i < sz(cnt); i++) {
                cnt[i] += cnt[i - 1];
            }
            for (int i = n - 1; i >= 0; i--) {
                idx[--cnt[rnk[i + d]]] = i;
            }
            fill(all(cnt), 0);
            for (int i = 0; i < n; i++) {
                ++cnt[rnk[i]];
            }
            for (int i = 1; i < sz(cnt); i++) {
                cnt[i] += cnt[i - 1];
            }
            for (int i = n - 1; i >= 0; i--) {
                sa[--cnt[rnk[idx[i]]]] = idx[i];
            }
            rnk_nxt[sa[0]] = 1;
            for (int i = 1; i < n; i++) {
                rnk_nxt[sa[i]] = rnk_nxt[sa[i - 1]] + (rnk[sa[i - 1]] != rnk[sa[i]] || rnk[sa[i - 1] + d] != rnk[sa[i] + d]);
            }
            swap(rnk, rnk_nxt);
            if (rnk[sa[n - 1]] == n) {
                break;
            }
        }
        for (int i = 0; i < n; i++) {
            --rnk[i];
        }
        for (int i = 0, k = 0; i < n; i++) {
            if (rnk[i] != n - 1) {
                int j = sa[rnk[i] + 1];
                while (i + k < n && j + k < n && s[i + k] == s[j + k]) {
                    ++k;
                }
                lcp[rnk[i]] = k ? k-- : 0;
            }
        }
    }
};