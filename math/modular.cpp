int fact[MAXN] = { 1,1 }, inv[MAXN] = { 1,1 }, fact_inv[MAXN] = { 1,1 };

void init() {
    for (int i = 2; i < MAXN; i++) {
        fact[i] = ll(fact[i - 1]) * i % mod;
    }
    for (int i = 2; i < MAXN; i++) {
        inv[i] = ll(inv[mod % i]) * (mod - mod / i) % mod;
    }
    for (int i = 2; i < MAXN; i++) {
        fact_inv[i] = ll(fact_inv[i - 1]) * inv[i] % mod;
    }
}

int nCr(int n, int r) {
    return n >= r && r >= 0 ? ll(fact[n]) * fact_inv[n - r] % mod * fact_inv[r] % mod : 0;
}

int nPr(int n, int r) {
    return n >= r && r >= 0 ? ll(fact[n]) * fact_inv[n - r] % mod : 0;
}