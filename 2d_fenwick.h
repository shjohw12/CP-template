struct Bit2 {
    int x_size, x_bias, y_size, y_bias;
    int node[MAXN][MAXN];

    void init(int x1, int x2, int y1, int y2) {
        x_size = x2 - x1 + 1, x_bias = 1 - x1;
        y_size = y2 - y1 + 1, y_bias = 1 - y1;
    }

    int solve(int x, int y) {
        x += x_bias;
        y += y_bias;
        int ret = 0;
        for (; x > 0; x -= x & -x) {
            for (int j = y; j > 0; j -= j & -j) {
                ret += node[x][j];
            }
        }
        return ret;
    }

    void update(int x, int y, int val) {
        x += x_bias;
        y += y_bias;
        for (; x <= x_size; x += x & -x) {
            for (int j = y; j <= y_size; j += j & -j) {
                node[x][j] += val;
            }
        }
    }
} bit;