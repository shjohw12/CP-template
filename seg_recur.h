template<typename T>
struct Seg {
    int st, en, le, ri, idx, k;
    T I, val;
    vector<T> node;

    T merge(T L, T R) {
        return L + R;
        // return min(L, R);
        // return max(L, R);
    }

    Seg(int st, int en, T I) {
        this->st = st, this->en = en;
        this->I = I;
        node.resize((en - st + 1) * 4, I);
    }

    Seg(int st, int en, auto origin, T I) {
        this->st = st, this->en = en;
        this->I = I;
        node.resize((en - st + 1) * 4);
        init(1, st, en, origin);
    }

    void init(int st, int en, T I) {
        this->st = st, this->en = en;
        this->I = I;
        node.resize((en - st + 1) * 4);
        fill(all(node), I);
    }

    void init(int st, int en, auto origin, T I) {
        this->st = st, this->en = en;
        this->I = I;
        node.resize((en - st + 1) * 4);
        init(1, st, en, origin);
    }

    void init(int nidx, int st, int en, auto origin) {
        if (st == en) {
            node[idx] = origin[st];
            return;
        }
        int mid = (st + en) >> 1;
        init(nidx << 1, st, mid, origin);
        init(nidx << 1 | 1, mid + 1, en, origin);
        node[idx] = merge(node[idx << 1], node[idx << 1 | 1]);
    }

    T solve(int le, int ri) {
        this->le = le, this->ri = ri;
        return solve(1, st, en);
    }

    T solve(int nidx, int st, int en) {
        if (st > ri || en < le || le > ri) {
            return I;
        }
        if (le <= st && en <= ri) {
            return node[nidx];
        }
        int mid = (st + en) >> 1;
        return merge(solve(nidx << 1, st, mid), solve(nidx << 1 | 1, mid + 1, en));
    }

    void update(int idx, T val) {
        this->idx = idx, this->val = val;
        update(1, st, en);
    }

    void update(int nidx, int st, int en) {
        if (st == en) {
            node[idx] = val;
            // node[idx] = merge(node[idx], val);
            return;
        }
        int mid = (st + en) >> 1;
        if (idx <= mid) {
            update(nidx << 1, st, mid);
        }
        else {
            update(nidx << 1 | 1, mid + 1, en);
        }
        node[idx] = merge(node[idx << 1], node[idx << 1 | 1]);
    }

    // int find_kth(int k) {
    //     this->k = k;
    //     return find_kth(1, st, en);
    // }

    // int find_kth(int nidx, int st, int en) {
    //     if (st == en) {
    //         return st;
    //     }
    //     int mid = (st + en) >> 1;
    //     if (node[nidx << 1] >= k) {
    //         return find_kth(nidx << 1, st, mid);
    //     }
    //     k -= node[nidx << 1];
    //     return find_kth(nidx << 1 | 1, mid + 1, en);
    // }
};