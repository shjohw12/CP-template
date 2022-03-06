template<typename T>
struct Bit {
    int node_size, bias;
    T I;
    vector<T> node;

    T merge(T L, T R) {
        return L + R;
        // return min(L, R);
        // return max(L, R);
    }

    Bit(int st, int en, T I) {
        node_size = en - st + 1;
        bias = 1 - st;
        this->I = I;
        node.resize(node_size + 1, I);
    }

    Bit(int st, int en, auto origin, T I) {
        node_size = en - st + 1;
        bias = 1 - st;
        this->I = I;
        node.resize(node_size + 1);
        for (int i = 1, j = st; j <= en; i++, j++) {
            node[i] = origin[j];
        }
        for (int i = 1; i <= node_size; i++) {
            int j = i + (i & -i);
            if (j <= node_size) {
                node[j] = merge(node[j], node[i]);
            }
        }
    }

    void init(int st, int en, T I) {
        node_size = en - st + 1;
        bias = 1 - st;
        this->I = I;
        node.resize(node_size + 1);
        fill(all(node), I);
    }

    void init(int st, int en, auto origin, T I) {
        node_size = en - st + 1;
        bias = 1 - st;
        this->I = I;
        node.resize(node_size + 1);
        for (int i = 1, j = st; j <= en; i++, j++) {
            node[i] = origin[j];
        }
        for (int i = 1; i <= node_size; i++) {
            int j = i + (i & -i);
            if (j <= node_size) {
                node[j] = merge(node[j], node[i]);
            }
        }
    }

    T solve(int idx) {
        T ret = I;
        for (idx += bias; idx > 0; idx -= idx & -idx) {
            ret = merge(ret, node[idx]);
        }
        return ret;
    }

    void update(int idx, T val) {
        for (idx += bias; idx <= node_size; idx += idx & -idx) {
            node[idx] = merge(node[idx], val);
        }
    }

    // int find_kth(int k) {
    //     int sum = 0, pos = 0;
    //     for (int i = __lg(node_size); i >= 0; i--) {
    //         int pos_nxt = pos | (1 << i);
    //         if (pos_nxt < node_size && sum + node[pos_nxt] < k) {
    //             pos = pos_nxt;
    //             sum += node[pos];
    //         }
    //     }
    //     return pos + 1 - bias;
    // }
};