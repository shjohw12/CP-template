struct Bct {
    struct Node {
        bool cut, bridge;
        vector<int> adj;
    };

    int n, num, bctnum; // dfs number, bct number is 1-based.
    vector<vector<pi>> adj;
    vector<Node> bct; // 단절점의 경우 그 자체가 노드, 아닌 경우 그 정점이 속한 BCC가 노드
    vector<int> in, low, vtxinv, edgeinv, stk, cut;
    vector<pi> edge; // edge number is 0-based. first < second

    Bct(int n) : n(n), num(0), bctnum(0), adj(n), bct(2 * n), in(n), low(n), vtxinv(n), edgeinv(n) {}

    // edge number is 1-based.
    void addedge(int a, int b) {
        if (a > b) {
            swap(a, b);
        }
        edge.emplace_back(a, b);
    }

    void dfs(int cur, int p = -1) {
        ++num;
        in[cur] = low[cur] = num;
        int chd = 0;
        bool flag = false;
        for (auto [nxt, edgenum] : adj[cur]) {
            if (nxt == p || in[cur] < in[nxt]) {
                continue;
            }
            stk.push_back(edgenum);
            if (in[nxt] == 0) {
                ++chd;
                dfs(nxt, cur);
                low[cur] = min(low[cur], low[nxt]);
                // bcc
                if (in[cur] <= low[nxt]) {
                    flag = true;
                    ++bctnum;
                    while (1) {
                        int top = stk.back();
                        stk.pop_back();
                        auto [u, v] = edge[top];
                        vtxinv[u] = vtxinv[v] = edgeinv[top] = bctnum;
                        if (top == edgenum) {
                            break;
                        }
                    }
                    // bridge
                    if (in[cur] < low[nxt]) {
                        bct[bctnum].bridge = true;
                    }
                }
            }
            else {
                low[cur] = min(low[cur], in[nxt]);
            }
        }
        if (p == -1) {
            if (chd >= 2) {
                cut.push_back(cur);
            }
        }
        else {
            if (flag) {
                cut.push_back(cur);
            }
        }
    }

    void make_tree() {
        sort(all(edge));
        for (int i = 0; i < sz(edge); i++) {
            auto [a, b] = edge[i];
            adj[a].emplace_back(b, i);
            adj[b].emplace_back(a, i);
        }
        for (int i = 0; i < n; i++) {
            if (in[i] == 0) {
                dfs(i);
            }
        }
        for (auto x : cut) {
            ++bctnum;
            bct[bctnum].cut = true;
            vtxinv[x] = bctnum;
            for (auto [_, edgenum] : adj[x]) {
                int nxt = edgeinv[edgenum];
                bct[bctnum].adj.push_back(nxt);
                bct[nxt].adj.push_back(bctnum);
            }
        }
    }
};