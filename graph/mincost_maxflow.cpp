struct MCMF {
    struct Edge {
        int nxt, cap, cost, ridx;
    };

    int src, snk;
    vector<int> dist, work;
    vector<uint8_t> vis;
    vector<vector<Edge>> adj;
    vector<int> que;

    MCMF(int n, int src, int snk) : src(src), snk(snk), dist(n + 5), work(n + 5), vis(n + 5), adj(n + 5) {}

    void addedge(int st, int en, int cap, int cost) {
        adj[st].push_back({ en, cap, cost, sz(adj[en]) });
        adj[en].push_back({ st, 0, -cost, sz(adj[st]) - 1 });
    }

    bool spfa() {
        fill(all(dist), inf);
        fill(all(vis), false);

        que.clear();
        que.push_back(src);
        dist[src] = 0;

        for (int top = 0; top < sz(que); top++) {
            int cur = que[top];
            vis[cur] = false;
            for (auto &[nxt, cap, cost, _] : adj[cur]) {
                if (cap > 0 && dist[nxt] > dist[cur] + cost) {
                    dist[nxt] = dist[cur] + cost;
                    if (vis[nxt] == false) {
                        que.push_back(nxt);
                        vis[nxt] = true;
                    }
                }
            }
        }

        return dist[snk] != inf;
    }

    int dfs(int cur, int flow) {
        if (cur == snk) {
            return flow;
        }

        vis[cur] = true;

        for (int &i = work[cur]; i < sz(adj[cur]); i++) {
            auto &[nxt, cap, cost, ridx] = adj[cur][i];
            if (vis[nxt] || cap == 0 || dist[nxt] != dist[cur] + cost) {
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

    pi solve() {
        pi ret = pi(0, 0);
        while (spfa()) {
            fill(all(work), 0);
            for (int flow = dfs(src, inf); flow; flow = dfs(src, inf)) {
                ret.first += flow;
                ret.second += flow * dist[snk];
            }
        }
        return ret;
    }
};