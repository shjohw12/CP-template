// MAXN = 패턴 개수 * 패턴 크기
// MAXC = 문자 개수

struct Trie {
    int chd[MAXN][MAXC];
    int fail[MAXN]; // 실패링크 = (나 자신이 아닌) 가장 긴 접미사
    int output[MAXN]; // 출력링크 = 접미사 중에 가장 긴 패턴의 끝
    int inv[MAXN]; // node가 몇번째 패턴의 끝? (없다면 0)
    int match[MAXN]; // node의 접미사 중 패턴의 개수(즉, node를 밟는 순간 증가하는 패턴 매칭의 수)
    int cnt[MAXN]; // cnt[i] = i번째 패턴의 등장 횟수
    int size = 1; // node 개수
    int n = 0; // 패턴 개수
    vector<int> que;

    int c2i(char c) {
        // return c - 'a';
        // return c - 'A';
        // return c - '0';
    }

    // 패턴 삽입
    void add(string s) {
        ++n;
        int cur = 0;
        for (auto i : s) {
            int nxt = c2i(i);
            if (chd[cur][nxt] == 0) {
                inv[size] = 0;
                match[size] = 0;
                chd[cur][nxt] = size++;
            }
            cur = chd[cur][nxt];
        }
        inv[cur] = n;
        match[cur] = 1;
    }

    // bfs로 실패링크와 출력링크 만들기
    void init() {
        que.clear();
        for (int i = 0; i < MAXC; i++) {
            // 루트가 가리키는 노드의 실패링크는 루트이다
            if (chd[0][i]) {
                fail[chd[0][i]] = 0;
                que.push_back(chd[0][i]);
            }
        }
        for (int top = 0; top < sz(que); top++) {
            int cur = que[top];
            // 실패 링크의 매칭 수를 더한다
            match[cur] += match[fail[cur]];
            // 출력링크는 내가 패턴의 끝이라면 나 자신이 되고, 그렇지 않으면 실패링크의 출력링크이다
            if (inv[cur]) {
                output[cur] = cur;
            }
            else {
                output[cur] = output[fail[cur]];
            }
            for (int i = 0; i < MAXC; i++) {
                // chd[cur][i] = 나 -> i
                if (chd[cur][i]) {
                    // 나의 실패링크 prv
                    int prv = fail[cur];
                    // 루트 또는 i를 가리키는 노드가 있을 때까지 실패링크를 타고 이동
                    while (prv && chd[prv][i] == 0) {
                        prv = fail[prv];
                    }
                    // 그러한 prv를 찾았고 (prv -> i)는 (나 -> i)의 실패링크가 된다
                    fail[chd[cur][i]] = chd[prv][i];
                    que.push_back(chd[cur][i]);
                }
            }
        }
    }

    void solve(string s) {
        memset(cnt, 0, sizeof(int) * (n + 5));
        int cur = 0;
        // 문자열 s에서 패턴 검색
        for (auto i : s) {
            int nxt = c2i(i);
            while (cur && chd[cur][nxt] == 0) {
                cur = fail[cur];
            }
            cur = chd[cur][nxt];
            if (output[cur]) {
                ++cnt[inv[output[cur]]];
            }
        }

        // 패턴 등장 횟수 계산
        vector<int> ord;
        que.clear();
        que.push_back(0);
        for (int top = 0; top < sz(que); top++) {
            cur = que[top];
            ord.push_back(cur);
            for (int i = 0; i < MAXC; i++) {
                if (chd[cur][i]) {
                    que.push_back(chd[cur][i]);
                }
            }
        }
        reverse(all(ord));
        for (auto i : ord) {
            if (inv[i] && output[fail[i]]) {
                cnt[inv[output[fail[i]]]] += cnt[inv[i]];
            }
        }
    }

    void clear() {
        memset(chd, 0, sizeof(int) * size * MAXC);
        size = 1, n = 0;
    }
} trie;