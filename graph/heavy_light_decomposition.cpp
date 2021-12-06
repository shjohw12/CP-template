vector<int> adj[MAXN];
int par[MAXN], sub[MAXN];
int in[MAXN], inv[MAXN], top[MAXN], dep[MAXN];
int num = 0;

// i를 루트로 하는 서브트리
// in[i] ~ in[i] + sub[i] - 1

// i를 포함하는 체인의 꼭대기 정점부터 i까지
// in[top[i]] ~ in[i]

void getsub(int cur) {
    sub[cur] = 1;

    if (sz(adj[cur]) >= 2 && adj[cur][0] == par[cur]) {
        swap(adj[cur][0], adj[cur][1]);
    }

    for (int i = 0; i < sz(adj[cur]); i++) {
        if (adj[cur][i] == par[cur]) {
            continue;
        }
        par[adj[cur][i]] = cur;
        getsub(adj[cur][i]);
        sub[cur] += sub[adj[cur][i]];
        if (sub[adj[cur][i]] > sub[adj[cur][0]]) {
            swap(adj[cur][i], adj[cur][0]);
        }
    }
}

void hld(int cur) {
    ++num;
    in[cur] = num;
    inv[num] = cur;

    for (auto nxt : adj[cur]) {
        if (nxt == par[cur]) {
            continue;
        }
        top[nxt] = nxt == adj[cur][0] ? top[cur] : nxt;
        dep[nxt] = dep[cur] + (nxt != adj[cur][0]);
        in[nxt] = in[cur] + 1;
        hld(nxt);
    }
}

int getlca(int a, int b) {
    while (top[a] != top[b]) {
        if (dep[a] < dep[b]) {
            swap(a, b);
        }
        a = par[top[a]];
    }
    return in[a] < in[b] ? a : b;
}