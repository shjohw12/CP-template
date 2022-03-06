struct Pst {
    // N = the number of trees
    // size = the number of nodes
    int st, en, N, size, le, ri, idx, val;
    int node[20 * MAXN];
    pi chd[20 * MAXN];
    int root[MAXN];

    void init(int st, int en) {
        this->st = st, this->en = en;
        N = 0;
        size = 1;
        init(0, st, en);
    }

    void init(int nidx, int st, int en) {
        node[nidx] = 0;
        if (st == en) {
            return;
        }
        int mid = (st + en) >> 1;
        init(chd[nidx].first = size++, st, mid);
        init(chd[nidx].second = size++, mid + 1, en);
    }

    // copy k-th tree to make new tree
    void add(int k, int idx, int val) {
        ++N;
        root[N] = size;
        node[size] = node[root[k]];
        chd[size] = chd[root[k]];
        this->idx = idx, this->val = val;
        update(size++, st, en);
    }

    void update(int nidx, int st, int en) {
        if (st == en) {
            node[nidx] += val;
            // node[nidx].val = val;
            return;
        }
        int mid = (st + en) >> 1;
        if (idx <= mid) {
            int lidx = chd[nidx].first;
            chd[nidx].first = size;
            node[size] = node[lidx];
            chd[size] = chd[lidx];
            update(size++, st, mid);
        }
        else {
            int ridx = chd[nidx].second;
            chd[nidx].second = size;
            node[size] = node[ridx];
            chd[size] = chd[ridx];
            update(size++, mid + 1, en);
        }
        node[nidx] = node[chd[nidx].first] + node[chd[nidx].second];
    }

    // k-th tree query
    int solve(int k, int le, int ri) {
        this->le = le, this->ri = ri;
        return _solve(root[k], st, en);
    }

    int _solve(int nidx, int st, int en) {
        if (st > ri || en < le || le > ri) {
            return 0;
        }
        if (le <= st && en <= ri) {
            return node[nidx];
        }
        int mid = (st + en) >> 1;
        return _solve(chd[nidx].first, st, mid) + _solve(chd[nidx].second, mid + 1, en);
    }

    // remove k trees most recently added
    void remove(int k) {
        size = root[N - k + 1];
        N -= k;
    }
} pst;