vector<int> adj[MAXN];
int par[MAXN], sub[MAXN], lv[MAXN];
int in[MAXN], inv[MAXN], top[MAXN], dep[MAXN];
int num = 0;

// i를 루트로 하는 서브트리
// in[i] ~ in[i] + sub[i] - 1

// i를 포함하는 체인의 꼭대기 정점부터 i까지
// in[top[i]] ~ in[i]

void getsub(int cur) {
    sub[cur] = 1;
    for (int i = 0; i < sz(adj[cur]); i++) {
        if (i == 0 && adj[cur][0] == par[cur]) {
            swap(adj[cur][0], adj[cur].back());
        }
        int nxt = adj[cur][i];
        if (nxt != par[cur]) {
            par[nxt] = cur;
            lv[nxt] = lv[cur] + 1;
            getsub(nxt);
            sub[cur] += sub[nxt];
            if (sub[nxt] > sub[adj[cur][0]]) {
                swap(adj[cur][i], adj[cur][0]);
            }
        }
    }
}

void hld(int cur) {
    ++num;
    in[cur] = num;
    inv[num] = cur;
    for (int i = 0; i < sz(adj[cur]); i++) {
        int nxt = adj[cur][i];
        if (nxt != par[cur]) {
            top[nxt] = i == 0 ? top[cur] : nxt;
            dep[nxt] = dep[cur] + (i != 0);
            hld(nxt);
        }
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