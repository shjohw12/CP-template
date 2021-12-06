int eea(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int q = a / b;
    int ret = eea(b, a - b * q, x, y);
    tie(x, y) = pair(y, x - y * q);
    return ret;
}

// ax = b (mod n) (0 <= b < n)
// cx = d (mod m) (0 <= d < m)
int crt(int a, int b, int n, int c, int d, int m) {
    int g = gcd(a, b);
    a /= g, b /= g, n /= gcd(n, g);

    int inv, _;
    if (eea(a, n, inv, _) != 1) {
        return -1;
    }
    b *= inv;

    g = gcd(c, d);
    c /= g, d /= g, m /= gcd(m, g);

    if (eea(c, m, inv, _) != 1) {
        return -1;
    }
    d *= inv;

    g = eea(n, m, inv, _);
    if ((d - b) % g) {
        return -1;
    }
    n /= g;
    m *= n;
    // now, m is new modular

    int ret = (__int128(n) * inv % m * (d - b) + b) % m;
    if (ret < 0) {
        ret += m;
    }
    return ret;
}