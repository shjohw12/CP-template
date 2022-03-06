struct Flow {
    struct Edge {
        int nxt, cap, ridx;
        Edge(int nxt, int cap, int ridx) : nxt(nxt), cap(cap), ridx(ridx) {}
    };

    int n;
    int src, snk;
    vector<int> lv, work;
    vector<vector<Edge>> adj;
    vector<int> que;
    vector<int> vis;

    Flow(int n) : n(n), lv(n), work(n), adj(n) {}
    Flow(int n, int src, int snk) : n(n), src(src), snk(snk), lv(n), work(n), adj(n) {}

    void addedge(int st, int en, int cap) {
        adj[st].emplace_back(en, cap, sz(adj[en]));
        adj[en].emplace_back(st, 0, sz(adj[st]) - 1);
        // adj[st].emplace_back(en, cap, sz(adj[en]));
        // adj[en].emplace_back(st, cap, sz(adj[st]) - 1);
    }

    bool bfs() {
        fill(all(lv), -1);
        que.clear();
        que.push_back(src);
        lv[src] = 0;
        for (int top = 0; top < sz(que); top++) {
            int cur = que[top];
            for (auto &[nxt, cap, ridx] : adj[cur]) {
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

    // void dfs(int cur) {
    //     vis[cur] = 1;
    //     for (auto &[nxt, cap, ridx] : adj[cur]) {
    //         if (cap > 0 && vis[nxt] == 0) {
    //             dfs(nxt);
    //         }
    //     }
    // }

    // void find_cut() {
    //     vis.resize(n);
    //     dfs(src);
    // }

    // bool is_cut(int s, int t) {
    //     return vis[s] && vis[t] == 0;
    // }
};