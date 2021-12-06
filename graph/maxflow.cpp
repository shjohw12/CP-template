struct Dinic {
    struct Edge {
        int nxt, cap, ridx;
    };

    int src, snk;
    vector<int> lv, work;
    vector<vector<Edge>> adj;
    vector<int> que;

    Dinic(int n, int src, int snk) : src(src), snk(snk), lv(n + 5), work(n + 5), adj(n + 5) {}

    void addedge(int st, int en, int cap) {
        adj[st].push_back({ en, cap, sz(adj[en]) });
        adj[en].push_back({ st, 0, sz(adj[st]) - 1 });

        // adj[st].push_back({ en, cap, sz(adj[en]) });
        // adj[en].push_back({ st, cap, sz(adj[st]) - 1 });
    }

    bool bfs() {
        fill(all(lv), -1);
        que.clear();
        que.push_back(src);
        lv[src] = 0;

        for (int top = 0; top < sz(que); top++) {
            int cur = que[top];
            for (auto &[nxt, cap, _] : adj[cur]) {
                if (lv[nxt] != -1 || cap == 0) {
                    continue;
                }
                lv[nxt] = lv[cur] + 1;
                que.push_back(nxt);
            }
        }

        return lv[snk] != -1;
    }

    int dfs(int cur, int flow) {
        if (cur == snk) {
            return flow;
        }
        for (int &i = work[cur]; i < sz(adj[cur]); i++) {
            auto &[nxt, cap, ridx] = adj[cur][i];
            if (lv[nxt] != lv[cur] + 1 || cap == 0) {
                continue;
            }
            int &rcap = adj[nxt][ridx].cap;
            int ret = dfs(nxt, min(flow, cap));
            if (ret) {
                cap -= ret;
                rcap += ret;
                return ret;
            }
        }
        return 0;
    }

    int solve() {
        int ret = 0;
        while (bfs()) {
            fill(all(work), 0);
            for (int flow = dfs(src, inf); flow; flow = dfs(src, inf)) {
                ret += flow;
            }
        }
        return ret;
    }
};