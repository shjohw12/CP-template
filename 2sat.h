struct Sat {
    int n, num, sccnum;
    vector<int> in, low, sccinv, tf, stk;
    vector<vector<int>> adj, scc;

    Sat(int n) : n(n), num(0), sccnum(0), in(2 * n), low(2 * n), sccinv(2 * n), tf(n), adj(2 * n), scc(2 * n) {}

    int nt(int x) {
        return 2 * n - 1 - x;
    }

    void addedge(int a, int b) {
        adj[a].push_back(b);
        adj[nt(b)].push_back(nt(a));
    }

    void dfs(int cur) {
        ++num;
        in[cur] = low[cur] = num;
        stk.push_back(cur);
        for (auto nxt : adj[cur]) {
            if (in[nxt] == 0) {
                dfs(nxt);
            }
            if (sccinv[nxt] == 0) {
                low[cur] = min(low[cur], low[nxt]);
            }
        }
        if (low[cur] == in[cur]) {
            ++sccnum;
            while (1) {
                int top = stk.back();
                stk.pop_back();
                sccinv[top] = sccnum;
                scc[sccnum].push_back(top);
                if (top == cur) {
                    break;
                }
            }
        }
    }

    bool solve() {
        for (int i = 0; i < 2 * n; i++) {
            if (in[i] == 0) {
                dfs(i);
            }
        }
        for (int i = 0; i < n; i++) {
            if (sccinv[i] == sccinv[nt(i)]) {
                return false;
            }
        }
        for (int i = 0; i < n; i++) {
            tf[i] = sccinv[i] < sccinv[nt(i)];
        }
        return true;
    }
};