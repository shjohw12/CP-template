int fact[MAXN], inv[MAXN], fact_inv[MAXN];
// int pw[MAXN], pw_inv[MAXN];

void init() {
    fact[0] = fact[1] = inv[1] = fact_inv[0] = fact_inv[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        fact[i] = ll(fact[i - 1]) * i % mod;
        inv[i] = ll(inv[mod % i]) * (mod - mod / i) % mod;
        fact_inv[i] = ll(fact_inv[i - 1]) * inv[i] % mod;
    }
    // pw[0] = pw_inv[0] = 1;
    // for (int i = 1; i < MAXN; i++) {
        // pw[i] = ll(pw[i - 1]) * 2 % mod;
        // pw_inv[i] = ll(pw_inv[i - 1]) * inv[2] % mod;
    // }
}

int nCr(int n, int r) {
    return n >= r && r >= 0 ? ll(fact[n]) * fact_inv[n - r] % mod * fact_inv[r] % mod : 0;
}

int nPr(int n, int r) {
    return n >= r && r >= 0 ? ll(fact[n]) * fact_inv[n - r] % mod : 0;
}