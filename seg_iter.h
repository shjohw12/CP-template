template<typename T>
struct Seg {
    int node_size, bias;
    T I;
    vector<T> node;

    T merge(T L, T R) {
        return L + R;
        // return min(L, R);
        // return max(L, R);
    }

    void init(int st, int en, T I) {
        node_size = en - st + 1;
        bias = -st;
        this->I = I;
        node.resize(node_size * 2);
        fill(all(node), I);
    }

    void init(int st, int en, auto origin, T I) {
        node_size = en - st + 1;
        bias = -st;
        this->I = I;
        node.resize(node_size * 2);
        for (int i = node_size, j = st; j <= en; i++, j++) {
            node[i] = origin[j];
        }
        for (int i = node_size - 1; i; i--) {
            node[i] = merge(node[i << 1], node[i << 1 | 1]);
        }
    }

    T solve(int le, int ri) {
        T ret = I;
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
        for (idx >>= 1; idx; idx >>= 1) {
            node[idx] = merge(node[idx << 1], node[idx << 1 | 1]);
        }
    }
};