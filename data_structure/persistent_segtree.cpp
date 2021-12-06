struct PST {
    // K = the number of trees
    // size = the number of nodes
    int st, en, K, size, le, ri, idx, val;
    int A[20 * MAXN];
    pi chd[20 * MAXN];
    int root[MAXN];

    void init(int st, int en) {
        this->st = st, this->en = en;
        K = 0;
        size = 1;
        init(0, st, en);
    }

    void init(int nidx, int st, int en) {
        A[nidx] = 0;
        if (st == en) {
            return;
        }
        int mid = (st + en) >> 1;

        init(chd[nidx].first = size++, st, mid);
        init(chd[nidx].second = size++, mid + 1, en);
    }

    // p번째 트리 복사하여 새로운 트리 생성
    void add(int idx, int val, int p) {
        ++K;
        root[K] = size;

        A[size] = A[root[p]];
        chd[size] = chd[root[p]];
        this->idx = idx, this->val = val;
        update(size++, st, en);
    }

    void update(int nidx, int st, int en) {
        if (st == en) {
            A[nidx] += val;
            // A[nidx].val = val;

            return;
        }

        int mid = (st + en) >> 1;

        if (idx <= mid) {
            int lidx = chd[nidx].first;
            chd[nidx].first = size;
            A[size] = A[lidx];
            chd[size] = chd[lidx];

            update(size++, st, mid);
        }
        else {
            int ridx = chd[nidx].second;
            chd[nidx].second = size;
            A[size] = A[ridx];
            chd[size] = chd[ridx];

            update(size++, mid + 1, en);
        }

        A[nidx] = A[chd[nidx].first] + A[chd[nidx].second];
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
            return A[nidx];
        }
        int mid = (st + en) >> 1;
        return _solve(chd[nidx].first, st, mid) + _solve(chd[nidx].second, mid + 1, en);
    }

    // remove k trees most recently added
    void remove(int k) {
        size = root[K - k + 1];
        K -= k;
    }
} pst;