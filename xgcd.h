int xgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int q = a / b;
    int ret = xgcd(b, a - b * q, x, y);
    tie(x, y) = pair(y, x - y * q);
    return ret;
}