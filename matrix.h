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
    Matrix(int n) : A(n, vector<int>(n)) {}

    vector<int> &operator[](int i) {
        return A[i];
    }

    Matrix operator+(Matrix &B) {
        int n = sz(A);
        Matrix ret(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ret[i][j] = A[i][j];
                add(ret[i][j], B[i][j]);
            }
        }
        return ret;
    }

    void operator+=(Matrix &B) {
        int n = sz(A);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                add(A[i][j], B[i][j]);
            }
        }
    }

    Matrix operator*(Matrix &B) {
        int n = sz(A);
        Matrix ret(n);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                ll t = A[i][k];
                for (int j = 0; j < n; j++) {
                    add(ret[i][j], t * B[k][j] % mod);
                }
            }
        }
        return ret;
    }

    void POW(int b) {
        Matrix &a = *this;
        int n = sz(A);
        Matrix ret(n);
        for (int i = 0; i < n; i++) {
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