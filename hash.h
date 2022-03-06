using namespace __gnu_pbds;
using ull = unsigned long long;
using hsh = pair<unsigned, unsigned>;
const unsigned mod = -1 ^ (1 << 31);
const hsh H = hsh(127, 131);

struct myhash {
    size_t operator()(const hsh &p) const {
        return hash<ull>()(ull(p.first) << 32 | p.second);
    };
};

using myset = gp_hash_table<hsh, null_type, myhash>;
using mymap = gp_hash_table<hsh, int, myhash>;

inline unsigned MOD(ull x) {
    x = (x >> 31) + (x & mod);
    return (x >> 31) + (x & mod);
}

hsh operator+(hsh l, hsh r) {
    if ((l.first += r.first) > mod) {
        l.first -= mod;
    }
    if ((l.second += r.second) > mod) {
        l.second -= mod;
    }
    return l;
}

void operator+=(hsh &l, hsh r) {
    if ((l.first += r.first) > mod) {
        l.first -= mod;
    }
    if ((l.second += r.second) > mod) {
        l.second -= mod;
    }
}

hsh operator-(hsh l, hsh r) {
    signed t = l.first - r.first;
    if (t <= 0) {
        t += mod;
    }
    l.first = t;
    t = l.second - r.second;
    if (t <= 0) {
        t += mod;
    }
    l.second = t;
    return l;
}

void operator-=(hsh &l, hsh r) {
    signed t = l.first - r.first;
    if (t <= 0) {
        t += mod;
    }
    l.first = t;
    t = l.second - r.second;
    if (t <= 0) {
        t += mod;
    }
    l.second = t;
}

hsh operator*(hsh l, hsh r) {
    l.first = MOD(ull(l.first) * r.first);
    l.second = MOD(ull(l.second) * r.second);
    return l;
}

void operator*=(hsh &l, hsh r) {
    l.first = MOD(ull(l.first) * r.first);
    l.second = MOD(ull(l.second) * r.second);
}

hsh pw[MAXN];

void init() {
    pw[0] = hsh(1, 1);
    for (int i = 1; i < MAXN; i++) {
        pw[i] = pw[i - 1] * H;
    }
}