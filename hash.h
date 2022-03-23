using hsh = pair<signed, signed>;
const ll mod = -1 ^ 1 << 31;
const hsh id = hsh(127, 131);

struct myhash {
    size_t operator()(hsh p) const {
        return hash<ll>()(ll(p.first) << 32 | p.second);
    };
};

inline signed MOD(ll x) {
    x = (x >> 31) + (x & mod);
    return (x >> 31) + (x & mod);
}

hsh operator+(hsh l, hsh r) {
    l = hsh(MOD(ll(l.first) + r.first), MOD(ll(l.second) + r.second));
    return l;
}

void operator+=(hsh &l, hsh r) {
    l = hsh(MOD(ll(l.first) + r.first), MOD(ll(l.second) + r.second));
}

hsh operator-(hsh l, hsh r) {
    l = hsh(MOD(l.first - r.first), MOD(l.second - r.second));
    return l;
}

void operator-=(hsh &l, hsh r) {
    l = hsh(MOD(l.first - r.first), MOD(l.second - r.second));
}

hsh operator*(hsh l, hsh r) {
    l = hsh(MOD(ll(l.first) * r.first), MOD(ll(l.second) * r.second));
    return l;
}

void operator*=(hsh &l, hsh r) {
    l = hsh(MOD(ll(l.first) * r.first), MOD(ll(l.second) * r.second));
}

hsh pw[MAXN];

void init() {
    pw[0] = hsh(1, 1);
    for (int i = 1; i < MAXN; i++) {
        pw[i] = pw[i - 1] * id;
    }
}