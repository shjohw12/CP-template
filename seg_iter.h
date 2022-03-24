template<typename T>
struct Seg {
    int node_size, bias;
    T id;
    vector<T> node;

    T merge(T L, T R) {
        return L + R;
        // return min(L, R);
        // return max(L, R);
    }

    void init(int st, int en, T id) {
        node_size = en - st + 1;
        bias = -st;
        this->id = id;
        node.resize(2 * node_size);
        fill(all(node), id);
    }

    void init(int st, int en, auto origin, T id) {
        node_size = en - st + 1;
        bias = -st;
        this->id = id;
        node.resize(2 * node_size);
        for (int i = node_size, j = st; j <= en; i++, j++) {
            node[i] = origin[j];
        }
        for (int i = node_size - 1; i > 0; i--) {
            node[i] = merge(node[i << 1], node[i << 1 | 1]);
        }
    }

    T solve(int le, int ri) {
        T ret = id;
        for (le += node_size + bias, ri += node_size + bias; le <= ri; le >>= 1, ri >>= 1) {
            if (le & 1) {
                ret = merge(ret, node[le]);
                ++le;
            }
            if (~ri & 1) {
                ret = merge(ret, node[ri]);
                --ri;
            }
        }
        return ret;
    }

    void update(int idx, T val) {
        idx += node_size + bias;
        node[idx] = val;
        // node[idx] = merge(node[idx], val);
        for (idx >>= 1; idx > 0; idx >>= 1) {
            node[idx] = merge(node[idx << 1], node[idx << 1 | 1]);
        }
    }
};