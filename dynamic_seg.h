struct Seg {
    int st, en, size, le, ri, idx, val, k;
    int node[MAXN];
    pi chd[MAXN];

    void init(int st, int en) {
        this->st = st, this->en = en;
        size = 1;
    }

    void update(int idx, int val) {
        this->idx = idx, this->val = val;
        update(0, st, en);
    }

    void update(int nidx, int st, int en) {
        if (st == en) {
            node[nidx] = val;
            // node[nidx] += val;
            return;
        }
        int mid = (st + en) >> 1;
        if (idx <= mid) {
            if (chd[nidx].first == 0) {
                chd[nidx].first = size++;
            }
            update(chd[nidx].first, st, mid);
        }
        else {
            if (chd[nidx].second == 0) {
                chd[nidx].second = size++;
            }
            update(chd[nidx].second, mid + 1, en);
        }
        int lidx = chd[nidx].first;
        int ridx = chd[nidx].second;
        node[nidx] = (lidx ? node[lidx] : 0) + (ridx ? node[ridx] : 0);
    }

    int solve(int le, int ri) {
        this->le = le, this->ri = ri;
        return solve(0, st, en);
    }

    int solve(int nidx, int st, int en) {
        if (st > ri || en < le || le > ri) {
            return 0;
        }
        if (le <= st && en <= ri) {
            return node[nidx];
        }
        int mid = (st + en) >> 1;
        int lidx = chd[nidx].first;
        int ridx = chd[nidx].second;
        return (lidx ? solve(lidx, st, mid) : 0) + (ridx ? solve(ridx, mid + 1, en) : 0);
    }

    int find_kth(int k) {
        this->k = k;
        return find_kth(0, st, en);
    }

    int find_kth(int nidx, int st, int en) {
        if (st == en) {
            return st;
        }
        int mid = (st + en) >> 1;
        int lidx = chd[nidx].first;
        if (lidx && node[lidx] >= k) {
            return find_kth(lidx, st, mid);
        }
        k -= lidx ? node[lidx] : 0;
        return find_kth(chd[nidx].second, mid + 1, en);
    }
} seg;