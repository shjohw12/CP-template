int mu[MAXN];

void init() {
    mu[1] = 1;
    for (int i = 1; i < MAXN; i++) {
        for (int j = i + i; j < MAXN; j += i) {
            mu[j] -= mu[i];
        }
    }
}