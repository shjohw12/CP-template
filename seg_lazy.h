template<typename T>
struct Seg {
    int st, en, le, ri, k;
    T I, lazyI, val;
    vector<T> node, lazy;

    T merge(T L, T R) {
        return L + R;
        return min(L, R);
        return max(L, R);
    }

    void to_lazy(int nidx, int st, int en, T val) {
        lazy[nidx << 1] += val;
        lazy[nidx << 1 | 1] += val;
        // lazy[nidx << 1] = val;
        // lazy[nidx << 1 | 1] = val;
    }

    void to_node(int nidx, int st, int en, T val) {
        node[nidx] += (en - st + 1) * val;
        // node[nidx] += val;
        // node[nidx] = val;
    }

    void init(int st, int en, T I, T lazyI) {
        this->st = st, this->en = en;
        this->I = I, this->lazyI = lazyI;
        node.resize((en - st + 1) * 4);
        fill(all(node), I);
        lazy.resize((en - st + 1) * 4);
        fill(all(node), lazyI);
    }

    void init(int st, int en, auto origin) {
        this->st = st, this->en = en;
        this->I = I, this->lazyI = lazyI;
        node.resize((en - st + 1) * 4);
        init(1, st, en, origin);
        lazy.resize((en - st + 1) * 4);
        fill(all(node), lazyI);
    }

    void init(int nidx, int st, int en, auto origin) {
        if (st == en) {
            node[nidx] = origin[st];
            return;
        }
        int mid = (st + en) >> 1;
        init(nidx << 1, st, mid, origin);
        init(nidx << 1 | 1, mid + 1, en, origin);
        node[nidx] = merge(node[nidx << 1], node[nidx << 1 | 1]);
    }

    void prop(int nidx, int st, int en) {
        if (lazy[nidx] == lazyI) {
            return;
        }
        to_node(nidx, st, en, lazy[nidx]);
        if (st != en) {
            to_lazy(nidx, st, en, lazy[nidx]);
        }
        lazy[nidx] = lazyI;
    }

    T solve(int le, int ri) {
        this->le = le, this->ri = ri;
        return solve(1, st, en);
    }

    T solve(int nidx, int st, int en) {
        prop(nidx, st, en);
        if (st > ri || en < le || le > ri) {
            return I;
        }
        if (le <= st && en <= ri) {
            return node[nidx];
        }
        int mid = (st + en) >> 1;
        return merge(solve(nidx << 1, st, mid), solve(nidx << 1 | 1, mid + 1, en));
    }

    void update(int le, int ri, T val) {
        this->le = le, this->ri = ri, this->val = val;
        _update(1, st, en);
    }

    void _update(int nidx, int st, int en) {
        prop(nidx, st, en);
        if (st > ri || en < le || le > ri) {
            return;
        }
        if (le <= st && en <= ri) {
            to_node(nidx, st, en, val);
            if (st != en) {
                to_lazy(nidx, st, en, val);
            }
            return;
        }
        int mid = (st + en) >> 1;
        _update(nidx << 1, st, mid);
        _update(nidx << 1 | 1, mid + 1, en);
        node[nidx] = merge(node[nidx << 1], node[nidx << 1 | 1]);
    }

    // int find_kth(int k) {
    //     this->k = k;
    //     return find_kth(1, st, en);
    // }

    // int find_kth(int nidx, int st, int en) {
    //     prop(nidx, st, en);
    //     if (st == en) {
    //         return st;
    //     }
    //     int mid = (st + en) >> 1;
    //     prop(nidx << 1, st, mid);
    //     if (node[nidx << 1] >= k) {
    //         return find_kth(nidx << 1, st, mid);
    //     }
    //     k -= node[nidx << 1];
    //     return find_kth(nidx << 1 | 1, mid + 1, en);
    // }
};