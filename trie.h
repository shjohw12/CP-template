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
        int nidx = 0;
        for (auto x : s) {
            int nxt = c2i(x);
            if (chd[nidx][nxt] == 0) {
                output[size] = false;
                chd[nidx][nxt] = size++;
            }
            nidx = chd[nidx][nxt];
        }
        output[nidx] = true;
    }

    int find(string s) {
        int nidx = 0;
        for (auto x : s) {
            int nxt = c2i(x);
            if (chd[nidx][nxt] == 0) {
                return 0;
            }
            nidx = chd[nidx][nxt];
        }
        return output[nidx] ? nidx : 0;
    }

    void clear() {
        memset(chd, 0, sizeof(int) * size * MAXC);
        size = 1;
    }
} trie;