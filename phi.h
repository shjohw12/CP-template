int phi[MAXN];

void init() {
    iota(phi, phi + MAXN, 0);
    for (int i = 1; i < MAXN; i++) {
        for (int j = i + i; j < MAXN; j += i) {
            phi[j] -= phi[i];
        }
    }
}