struct Bimatch {
    int n, m;
    vector<int> A, B, lv, work;
    vector<vector<int>> adj;
    vector<int> que;

    Bimatch(int n, int m) : n(n), m(m), A(n + 5), B(m + 5), lv(n + 5), work(n + 5), adj(n + 5) {}

    void addedge(int st, int en) {
        adj[st].push_back(en);
    }

    bool bfs() {
        fill(all(lv), -1);
        que.clear();
        for (int i = 0; i < n; i++) {
            if (A[i] == -1) {
                lv[i] = 0;
                que.push_back(i);
            }
        }
        bool ret = false;
        for (int top = 0; top < sz(que); top++) {
            int cur = que[top];
            for (auto nxt : adj[cur]) {
                if (B[nxt] == -1) {
                    ret = true;
                }
                else if (lv[B[nxt]] == -1) {
                    lv[B[nxt]] = lv[cur] + 1;
                    que.push_back(B[nxt]);
                }
            }
        }
        return ret;
    }

    bool dfs(int cur) {
        for (int &i = work[cur]; i < sz(adj[cur]); i++) {
            int nxt = adj[cur][i];
            if (B[nxt] == -1 || (lv[B[nxt]] == lv[cur] + 1 && dfs(B[nxt]))) {
                A[cur] = nxt;
                B[nxt] = cur;
                return true;
            }
        }
        return false;
    }

    int solve() {
        int ret = 0;
        fill(all(A), -1);
        fill(all(B), -1);
        while (bfs()) {
            fill(all(work), 0);
            for (int i = 0; i < n; i++) {
                if (A[i] == -1 && dfs(i)) {
                    ++ret;
                }
            }
        }
        return ret;
    }
};