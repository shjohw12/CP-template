struct Mcmf {
    struct Edge {
        int nxt, cap, cost, ridx;
        Edge(int nxt, int cap, int cost, int ridx) : nxt(nxt), cap(cap), cost(cost), ridx(ridx) {}
    };

    int n;
    int src, snk;
    vector<int> dist, work, vis;
    vector<vector<Edge>> adj;
    vector<int> que;

    Mcmf(int n) : n(n), dist(n), work(n), vis(n), adj(n) {}
    Mcmf(int n, int src, int snk) : n(n), src(src), snk(snk), dist(n), work(n), vis(n), adj(n) {}

    void addedge(int st, int en, int cap, int cost) {
        adj[st].emplace_back(en, cap, cost, sz(adj[en]));
        adj[en].emplace_back(st, 0, -cost, sz(adj[st]) - 1);
    }

    bool spfa() {
        fill(all(dist), inf);
        fill(all(vis), 0);
        que.clear();
        que.push_back(src);
        dist[src] = 0;
        for (int top = 0; top < sz(que); top++) {
            int cur = que[top];
            vis[cur] = 0;
            for (auto [nxt, cap, cost, ridx] : adj[cur]) {
                if (cap > 0 && dist[nxt] > dist[cur] + cost) {
                    dist[nxt] = dist[cur] + cost;
                    if (vis[nxt] == 0) {
                        que.push_back(nxt);
                        vis[nxt] = 1;
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
        vis[cur] = 1;
        for (int &i = work[cur]; i < sz(adj[cur]); i++) {
            auto &[nxt, cap, cost, ridx] = adj[cur][i];
            if (vis[nxt] == 0 && cap > 0 && dist[nxt] == dist[cur] + cost) {
                int &rcap = adj[nxt][ridx].cap;
                int ret = dfs(nxt, min(flow, cap));
                if (ret) {
                    cap -= ret;
                    rcap += ret;
                    return ret;
                }
            }
        }
        return 0;
    }

    // <flow, cost>
    pi solve() {
        pi ret = pi(0, 0);
        while (spfa()) {
            fill(all(work), 0);
            for (int flow = dfs(src, inf); flow > 0; flow = dfs(src, inf)) {
                ret.first += flow;
                ret.second += flow * dist[snk];
            }
        }
        return ret;
    }
};