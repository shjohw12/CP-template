struct SA {
    // group[i] = suffix[i] 의 그룹 번호
    // sa[i] = 사전순으로 i번째 접미사의 suffix 값
    // lcp[i] = 사전순으로 i, i+1번째 접미사의 최대 공통 prefix
    int n;
    string s;
    vector<int> group, tmp, sa, lcp, cnt;

    SA(string s) : n(sz(s)), s(s), group(n + 5), tmp(n + 5), sa(n + 5), lcp(n + 5), cnt(max(n, int(128)) + 5) {
        for (int i = 0; i < n; i++) {
            // sa는 0 ~ n-1 의 값 가짐
            sa[i] = i;
            // 처음에는 맨 앞 문자로 그룹 번호 부여
            group[i] = s[i];
        }
        group[n] = tmp[n] = 0;

        for (int k = 1;; k <<= 1) {
            // [k, 2k) 문자를 기준으로 counting sort
            fill(all(cnt), 0);
            for (int i = 0; i < n; i++) {
                ++cnt[group[min(i + k, n)]];
            }
            for (int i = 1; i < sz(cnt); i++) {
                cnt[i] += cnt[i - 1];
            }

            // tmp[i] = [k, 2k) 문자 기준으로 사전순으로 i번에 있어야 할 suffix 값
            for (int i = n - 1; i >= 0; i--) {
                tmp[--cnt[group[min(i + k, n)]]] = i;
            }

            // [0, k) 문자를 기준으로 counting sort
            fill(all(cnt), 0);
            for (int i = 0; i < n; i++) {
                ++cnt[group[i]];
            }
            for (int i = 1; i < sz(cnt); i++) {
                cnt[i] += cnt[i - 1];
            }

            // sa[i] = [0, 2k) 문자 기준으로 사전순으로 i번에 있어야 할 suffix 값
            for (int i = n - 1; i >= 0; i--) {
                sa[--cnt[group[tmp[i]]]] = tmp[i];
            }

            // tmp[sa[i]] = sa[i]의 그룹 번호, group의 임시 값
            tmp[sa[0]] = 1;
            for (int i = 1; i < n; i++) {
                tmp[sa[i]] = tmp[sa[i - 1]] + (group[sa[i - 1]] != group[sa[i]] || group[sa[i - 1] + k] != group[sa[i] + k]);
            }

            swap(group, tmp);

            if (group[sa[n - 1]] == n) {
                break;
            }
        }

        for (int i = 0; i < n; i++) {
            --group[i];
        }
        // 이제 group[sa[i]] = i가 성립
        // 즉, group[i] = sa의 역함수, suffix[i] 의 sa 값(suffix[i] 가 사전순으로 몇번째?)

        for (int i = 0, k = 0; i < n; i++) {
            if (group[i] == n - 1) {
                continue;
            }
            for (int j = sa[group[i] + 1]; s[i + k] == s[j + k]; k++);
            lcp[group[i]] = k;
            if (k) {
                --k;
            }
        }
    }
};