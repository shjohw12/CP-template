vector<int> adj[MAXN];
int par[MAXN], sub[MAXN];
bool vis[MAXN];
int tot = 0;

vector<int> centadj[MAXN];
int centpar[MAXN];

void getsub(int cur) {
    sub[cur] = 1;
    for (auto nxt : adj[cur]) {
        if (nxt != par[cur] && !vis[nxt]) {
            par[nxt] = cur;
            getsub(nxt);
            sub[cur] += sub[nxt];
        }
    }
}

int getcent(int cur) {
    for (auto nxt : adj[cur]) {
        if (nxt != par[cur] && !vis[nxt] && sub[nxt] > 2 * tot) {
            return getcent(nxt);
        }
    }
    return cur;
}

// make centroid tree
int decomp(int cur) {
    getsub(cur);
    tot = sub[cur];
    int cent = getcent(cur);
    vis[cent] = true;
    for (auto nxt : adj[cent]) {
        if (!vis[nxt]) {
            int nxtcent = decomp(nxt);
            centpar[nxtcent] = cent;
            centadj[cent].push_back(nxtcent);
        }
    }
    return cent;
}