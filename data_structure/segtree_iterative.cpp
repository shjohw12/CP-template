struct SEG {
    int node_size, bias;
    vector<int> A;

    SEG(int st, int en) : node_size(en - st + 1), bias(-st), A(node_size * 2 + 5) {}

    // SEG(int st, int en, auto origin) : node_size(en - st + 1), bias(-st), A(node_size * 2 + 5) {
    //     for (int i = node_size, j = st; j <= en; i++, j++) {
    //         A[i] = origin[j];
    //     }
    //     for (int i = node_size - 1; i; i--) {
    //         A[i] = A[i << 1] + A[i << 1 | 1];
    //         // A[i] = min(A[i << 1], A[i << 1 | 1]);
    //         // A[i] = max(A[i << 1], A[i << 1 | 1]);
    //     }
    // }

    // void init(int st, int en) {
    //     node_size = en - st + 1;
    //     bias = -st;
    //     A.resize(node_size * 2 + 5);
    // }

    // void init(int st, int en, auto origin) {
    //     node_size = en - st + 1;
    //     bias = -st;
    //     A.resize(node_size * 2 + 5);

    //     for (int i = node_size, j = st; j <= en; i++, j++) {
    //         A[i] = origin[j];
    //     }
    //     for (int i = node_size - 1; i; i--) {
    //         A[i] = A[i << 1] + A[i << 1 | 1];
    //         // A[i] = min(A[i << 1], A[i << 1 | 1]);
    //         // A[i] = max(A[i << 1], A[i << 1 | 1]);
    //     }
    // }

    int solve(int le, int ri) {
        int ret = 0;
        // int ret = inf;
        // int ret = minf;
        for (le += node_size + bias, ri += node_size + bias; le <= ri; le >>= 1, ri >>= 1) {
            if (le & 1) {
                ret += A[le];
                // ret = min(ret, A[le]);
                // ret = max(ret, A[le]);
                ++le;
            }
            if (~ri & 1) {
                ret += A[ri];
                // ret = min(ret, A[ri]);
                // ret = max(ret, A[ri]);
                --ri;
            }
        }
        return ret;
    }

    void update(int idx, int val) {
        idx += node_size + bias;

        A[idx] = val;
        // A[idx] += val;

        for (idx >>= 1; idx; idx >>= 1) {
            A[idx] = A[idx << 1] + A[idx << 1 | 1];
            // A[idx] = min(A[idx << 1], A[idx << 1 | 1]);
            // A[idx] = max(A[idx << 1], A[idx << 1 | 1]);
        }
    }
};