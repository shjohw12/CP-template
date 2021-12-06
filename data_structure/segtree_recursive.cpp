struct SEG {
    int st, en, le, ri, idx, val, k;
    vector<int> A;

    SEG(int st, int en) : st(st), en(en), A((en - st + 1) * 4 + 5) {}

    // SEG(int st, int en, auto origin) : st(st), en(en), A((en - st + 1) * 4 + 5) {
    //     init(1, st, en, origin);
    // }

    // void init(int st, int en) {
    //     this->st = st, this->en = en;
    //     A.resize((en - st + 1) * 4 + 5);
    // }

    // void init(int st, int en, auto origin) {
    //     this->st = st, this->en = en;
    //     A.resize((en - st + 1) * 4 + 5);

    //     init(1, st, en, origin);
    // }

    // void init(int nidx, int st, int en, auto origin) {
    //     if (st == en) {
    //         A[nidx] = origin[st];
    //         return;
    //     }
    //     int mid = (st + en) >> 1;

    //     init(nidx << 1, st, mid, origin);
    //     init(nidx << 1 | 1, mid + 1, en, origin);

    //     A[nidx] = A[nidx << 1] + A[nidx << 1 | 1];
    //     // A[nidx] = min(A[nidx << 1], A[nidx << 1 | 1]);
    //     // A[nidx] = max(A[nidx << 1], A[nidx << 1 | 1]);
    // }

    int solve(int le, int ri) {
        this->le = le, this->ri = ri;
        return solve(1, st, en);
    }

    int solve(int nidx, int st, int en) {
        if (st > ri || en < le || le > ri) {
            return 0;
            // return inf;
            // return minf;
        }
        if (le <= st && en <= ri) {
            return A[nidx];
        }
        int mid = (st + en) >> 1;
        return solve(nidx << 1, st, mid) + solve(nidx << 1 | 1, mid + 1, en);
        // return min(solve(nidx << 1, st, mid), solve(nidx << 1 | 1, mid + 1, en));
        // return max(solve(nidx << 1, st, mid), solve(nidx << 1 | 1, mid + 1, en));
    }

    void update(int idx, int val) {
        this->idx = idx, this->val = val;
        update(1, st, en);
    }

    void update(int nidx, int st, int en) {
        if (st == en) {
            A[nidx] = val;

            // A[nidx] += val;
            return;
        }
        int mid = (st + en) >> 1;
        if (idx <= mid) {
            update(nidx << 1, st, mid);
        }
        else {
            update(nidx << 1 | 1, mid + 1, en);
        }
        A[nidx] = A[nidx << 1] + A[nidx << 1 | 1];
        // A[nidx] = min(A[nidx << 1], A[nidx << 1 | 1]);
        // A[nidx] = max(A[nidx << 1], A[nidx << 1 | 1]);
    }

    int find_kth(int k) {
        this->k = k;
        return find_kth(1, st, en);
    }

    int find_kth(int nidx, int st, int en) {
        if (st == en) {
            return st;
        }
        int mid = (st + en) >> 1;
        if (A[nidx << 1] >= k) {
            return find_kth(nidx << 1, st, mid);
        }

        k -= A[nidx << 1];
        return find_kth(nidx << 1 | 1, mid + 1, en);
    }
};