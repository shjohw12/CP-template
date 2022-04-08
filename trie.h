// MAXN = 문자열 개수 * 문자열 크기
// MAXC = 문자 개수

struct Trie {
    int chd[MAXN][MAXC];
    bool output[MAXN];
    int size = 1;

    int c2i(char c) {
        // return c - 'a';
        // return c - 'A';
        // return c - '0';
    }

    void add(string s) {
        int cur = 0;
        for (auto i : s) {
            int nxt = c2i(i);
            if (chd[cur][nxt] == 0) {
                output[size] = false;
                chd[cur][nxt] = size++;
            }
            cur = chd[cur][nxt];
        }
        output[cur] = true;
    }

    int find(string s) {
        int cur = 0;
        for (auto i : s) {
            int nxt = c2i(i);
            if (chd[cur][nxt] == 0) {
                return -1;
            }
            cur = chd[cur][nxt];
        }
        return output[cur] ? cur : -1;
    }

    void clear() {
        memset(chd, 0, sizeof(int) * size * MAXC);
        size = 1;
    }
} trie;