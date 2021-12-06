void add(int &x, int y) {
    x += y;
    if (x >= mod) {
        x -= mod;
    }
    if (x < 0) {
        x += mod;
    }
}

struct Matrix {
    vector<vector<int>> A;
    Matrix(int n, int m) : A(n, vector<int>(m)) {}

    vector<int> &operator[](int i) {
        return A[i];
    }

    Matrix operator+(Matrix &B) {
        Matrix ret(sz(A), sz(A));
        for (int i = 0; i < sz(A); i++) {
            for (int j = 0; j < sz(A); j++) {
                ret[i][j] = A[i][j] + B[i][j];
                add(ret[i][j], 0);
            }
        }
        return ret;
    }

    void operator+=(Matrix &B) {
        for (int i = 0; i < sz(A); i++) {
            for (int j = 0; j < sz(A); j++) {
                add(A[i][j], B[i][j]);
            }
        }
    }

    Matrix operator*(Matrix &B) {
        Matrix ret(sz(A), sz(A));
        for (int i = 0; i < sz(A); i++) {
            for (int k = 0; k < sz(A); k++) {
                ll t = A[i][k];
                for (int j = 0; j < sz(A); j++) {
                    add(ret[i][j], t * B[k][j] % mod);
                }
            }
        }
        return ret;
    }

    void POW(int b) {
        Matrix &a = *this;
        Matrix ret(sz(A), sz(A));
        for (int i = 0; i < sz(A); i++) {
            ret[i][i] = 1;
        }
        for (; b; b >>= 1, a = a * a) {
            if (b & 1) {
                ret = ret * a;
            }
        }
        swap(a, ret);
    }
};