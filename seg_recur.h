template<typename T>
struct Seg {
    int st, en, le, ri, idx, k;
    T id, val;
    vector<T> node;

    T merge(T L, T R) {
        return L + R;
        // return min(L, R);
        // return max(L, R);
    }

    void init(int st, int en, T id) {
        this->st = st, this->en = en;
        this->id = id;
        node.resize(4 * (en - st + 1));
        fill(all(node), id);
    }

    void init(int st, int en, auto origin, T id) {
        this->st = st, this->en = en;
        this->id = id;
        node.resize(4 * (en - st + 1));
        _init(1, st, en, origin);
    }

    void _init(int nidx, int st, int en, auto origin) {
        if (st == en) {
            node[nidx] = origin[st];
            return;
        }
        int mid = (st + en) >> 1;
        _init(nidx << 1, st, mid, origin);
        _init(nidx << 1 | 1, mid + 1, en, origin);
        node[nidx] = merge(node[nidx << 1], node[nidx << 1 | 1]);
    }

    T solve(int le, int ri) {
        this->le = le, this->ri = ri;
        return solve(1, st, en);
    }

    T solve(int nidx, int st, int en) {
        if (st > ri || en < le || le > ri) {
            return id;
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
            node[nidx] = val;
            // node[nidx] = merge(node[nidx], val);
            return;
        }
        int mid = (st + en) >> 1;
        if (idx <= mid) {
            update(nidx << 1, st, mid);
        }
        else {
            update(nidx << 1 | 1, mid + 1, en);
        }
        node[nidx] = merge(node[nidx << 1], node[nidx << 1 | 1]);
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