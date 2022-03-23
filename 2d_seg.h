struct Seg2 {
    int x_size, y_size, x_bias, y_bias;
    int node[2 * MAXN][2 * MAXN];

    void init(int x1, int x2, int y1, int y2) {
        x_size = x2 - x1 + 1, x_bias = -x1;
        y_size = y2 - y1 + 1, y_bias = -y1;
    }

    int ysolve(int x, int y1, int y2) {
        int ret = 0;
        // int ret = inf;
        // int ret = minf;
        for (y1 += y_size + y_bias, y2 += y_size + y_bias; y1 <= y2; y1 >>= 1, y2 >>= 1) {
            if (y1 & 1) {
                ret += node[x][y1];
                // ret = min(ret, node[x][y1]);
                // ret = max(ret, node[x][y1]);
                ++y1;
            }
            if (~y2 & 1) {
                ret += node[x][y2];
                // ret = min(ret, node[x][y2]);
                // ret = max(ret, node[x][y2]);
                --y2;
            }
        }
        return ret;
    }

    int solve(int x1, int x2, int y1, int y2) {
        int ret = 0;
        // int ret = inf;
        // int ret = minf;
        for (x1 += x_size + x_bias, x2 += x_size + x_bias; x1 <= x2; x1 >>= 1, x2 >>= 1) {
            if (x1 & 1) {
                ret += ysolve(x1, y1, y2);
                // ret = min(ret, ysolve(x1, y1, y2));
                // ret = max(ret, ysolve(x1, y1, y2));
                ++x1;
            }
            if (~x2 & 1) {
                ret += ysolve(x2, y1, y2);
                // ret = min(ret, ysolve(x2, y1, y2));
                // ret = max(ret, ysolve(x2, y1, y2));
                --x2;
            }
        }
        return ret;
    }

    void update(int x, int y, int val) {
        x += x_size + x_bias;
        y += y_size + y_bias;
        node[x][y] = val;
        // node[x][y] += val;
        for (int j = y >> 1; j; j >>= 1) {
            node[x][j] = node[x][j << 1] + node[x][j << 1 | 1];
            // node[x][j] = min(node[x][j << 1], node[x][j << 1 | 1]);
            // node[x][j] = max(node[x][j << 1], node[x][j << 1 | 1]);
        }
        for (x >>= 1; x; x >>= 1) {
            for (int j = y; j; j >>= 1) {
                node[x][j] = node[x << 1][j] + node[x << 1 | 1][j];
                // node[x][j] = min(node[x][j << 1], node[x][j << 1 | 1]);
                // node[x][j] = max(node[x][j << 1], node[x][j << 1 | 1]);
            }
        }
    }
} seg;