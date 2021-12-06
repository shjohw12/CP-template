struct BIT {
    int node_size, bias;
    vector<int> A;

    BIT(int st, int en) : node_size(en - st + 1), bias(1 - st), A(node_size + 5) {}

    // BIT(int st, int en, auto origin) : node_size(en - st + 1), bias(1 - st), A(node_size + 5) {
    //     for (int i = 1, j = st; j <= en; i++, j++) {
    //         A[i] = origin[j];
    //     }

    //     for (int i = 1; i <= node_size; i++) {
    //         int j = i + (i & -i);
    //         if (j <= node_size) {
    //             A[j] += A[i];
    //         }
    //     }
    // }

    // void init(int st, int en) {
    //     node_size = en - st + 1;
    //     bias = 1 - st;
    //     A.resize(node_size + 5);
    // }

    // void init(int st, int en, auto origin) {
    //     node_size = en - st + 1;
    //     bias = 1 - st;
    //     A.resize(node_size + 5);

    //     for (int i = 1, j = st; j <= en; i++, j++) {
    //         A[i] = origin[j];
    //     }

    //     for (int i = 1; i <= node_size; i++) {
    //         int j = i + (i & -i);
    //         if (j <= node_size) {
    //             A[j] += A[i];
    //         }
    //     }
    // }

    int solve(int idx) {
        idx += bias;
        int ret = 0;
        for (; idx; idx -= idx & -idx) {
            ret += A[idx];
        }
        return ret;
    }

    void update(int idx, int val) {
        idx += bias;
        for (; idx <= node_size; idx += idx & -idx) {
            A[idx] += val;
        }
    }

    int find_kth(int k) {
        int sum = 0, pos = 0;
        for (int i = __lg(node_size); i >= 0; i--) {
            int pos_nxt = pos | (1 << i);
            if (pos_nxt < node_size && sum + A[pos_nxt] < k) {
                pos = pos_nxt;
                sum += A[pos];
            }
        }
        return pos + 1 - bias;
    }
};