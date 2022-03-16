using ld = long double;
// #define double ld
const double eps = 1e-9;
const double PI = M_PI;

template<typename T>
inline int sgn(T x) { return x < 0 ? -1 : x > 0; }

template<typename T>
struct point {
    using P = point;
    T x, y;
    explicit point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return pair(x, y) < pair(p.x, p.y); }
    bool operator<=(P p) const { return pair(x, y) <= pair(p.x, p.y); }
    bool operator>(P p) const { return pair(x, y) > pair(p.x, p.y); }
    bool operator>=(P p) const { return pair(x, y) >= pair(p.x, p.y); }
    bool operator==(P p) const { return pair(x, y) == pair(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    // cross product
    T operator*(P p) const { return x * p.y - y * p.x; }
    // dot product
    T dot(P p) const { return x * p.x + y * p.y; }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt(dist2()); }
    // angle to x-axis in interval [-PI, PI]
    double angle() const { return atan2(y, x); }
    // makes dist() = 1
    P unit() const { return *this / dist(); }
    // rotates +90 degrees
    P perp() const { return P(-y, x); }
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    friend ostream &operator<<(ostream &os, P p) {
        return os << '(' << p.x << ", " << p.y << ')';
    }
    friend T getDist2(P a, P b) {
        return (b - a).dist2();
    }
    friend T getDist(P a, P b) {
        return (b - a).dist();
    }
    friend T getArea(vector<P> &A) {
        int n = sz(A);
        T ret = 0;
        for (int i = 0; i < n; i++) {
            int j = i == n - 1 ? 0 : i + 1;
            ret += A[i] * A[j];
        }
        ret = abs(ret);
        return ret;
        // return ret / 2;
    }
    friend int ccw(P a, P b, P c) {
        return sgn((b - a) * (c - a));
    }
    friend int ccw(P a, P b, P c, P d) {
        return ccw(P(), b - a, d - c);
    }
    friend int ang(P a, P b, P c) {
        return sgn((a - b).dot(c - b));
    }
    friend double lineDist(P p, P a, P b) {
        return ((a - p) * (b - p)) / getDist(a, b);
    }
    friend double segDist(P p, P a, P b) {
        if (ang(a, b, p) == -1) {
            return getDist(p, a);
        }
        if (ang(b, a, p) == -1) {
            return getDist(p, b);
        }
        return lineDist(p, a, b);
    }
    friend bool segInter(P a, P b, P c, P d) {
        // AB를 기준으로 C의 위치
        int c1 = ccw(a, b, c);
        // AB를 기준으로 D의 위치
        int c2 = ccw(a, b, d);
        // 네 점이 일직선 위에 있는 경우
        if (c1 == 0 && c2 == 0) {
            if (a > b) {
                swap(a, b);
            }
            if (c > d) {
                swap(c, d);
            }
            // A C B D 또는 C A D B 또는 A C D B 또는 C A B D 순서이면 교차
            // B == C 또는 A == D 이면 한 점에서 만난다
            return c <= b && a <= d;
        }
        // CD를 기준으로 A의 위치
        int c3 = ccw(c, d, a);
        // CD를 기준으로 B의 위치
        int c4 = ccw(c, d, b);
        // C,D가 AB를 기준으로 반대쪽에, A,B가 CD를 기준으로 반대쪽에 있으면 교차
        return c1 != c2 && c3 != c4;
    }
    // graham scan
    friend vector<P> convexHull(vector<P> A) {
        vector<P> hull;
        swap(A[0], *min_element(all(A)));
        sort(A.begin() + 1, A.end(), [&](P l, P r) {
            int d = ccw(A[0], l, r);
            return d ? d == 1 : l < r;
        });
        for (auto p : A) {
            while (sz(hull) >= 2 && ccw(hull[sz(hull) - 2], hull.back(), p) <= 0) {
                hull.pop_back();
            }
            hull.push_back(p);
        }
        return hull;
    }
    // monotone chain
    friend pair<vector<P>, vector<P>> convexHull2(vector<P> A) {
        vector<P> uhull, dhull;
        sort(all(A));
        for (auto p : A) {
            while (sz(uhull) >= 2 && ccw(uhull[sz(uhull) - 2], uhull.back(), p) >= 0) {
                uhull.pop_back();
            }
            uhull.push_back(p);
            while (sz(dhull) >= 2 && ccw(dhull[sz(dhull) - 2], dhull.back(), p) <= 0) {
                dhull.pop_back();
            }
            dhull.push_back(p);
        }
        // dhull.insert(dhull.end(), next(uhull.rbegin()), prev(uhull.rend()));
        return pair(uhull, dhull);
    }
    // (가장 짧은 거리) ** 2
    friend T closestPair(vector<P> A) {
        set<P> se;
        sort(all(A), [](P l, P r) {
            return l.y < r.y;
        });
        pair<T, pair<P, P>> ret = pair(getDist2(A[0], A[1]), pair(A[0], A[1]));
        se.insert(A[0]);
        se.insert(A[1]);
        int i = 0;
        for (auto p : A) {
            P d = pair(1 + sqrt(ret.first), 0);
            while (A[i].y <= p.y - d.x) {
                se.erase(A[i++]);
            }
            auto lo = se.lower_bound(p - d), hi = se.upper_bound(p + d);
            for (; lo != hi; ++lo) {
                ret = min(ret, pair(getDist2(*lo, p), pair(*lo, p)));
            }
            se.insert(p);
        }
        return ret.first;
    }
    // (가장 먼 거리) ** 2
    friend T rotatingCalipers(vector<P> &A) {
        auto hull = convexHull(A);
        int n = sz(hull);
        pair<T, pair<P, P>> ret = pair(getDist2(A[0], A[1]), pair(A[0], A[1]));
        for (int i = 0, j = 1; j < n;) {
            ret = max(ret, pair(getDist2(A[i], A[j], pair(A[i], A[j]))));
            if (ccw(hull[i], hull[i + 1], hull[j], hull[j == n - 1 ? 0 : j + 1]) == 1) {
                ++i;
            }
            else {
                ++j;
            }
        }
        return ret.first;
    }
    // O(n)
    friend bool pointInPolygon(vector<P> &A, P p) {
        int n = sz(A);
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            // 다각형 변 위에 있는 경우
            if (ccw(p, A[i], A[i == n - 1 ? 0 : i + 1]) == 0) {
                if (min(A[i], A[i == n - 1 ? 0 : i + 1]) <= p && p <= max(A[i], A[i == n - 1 ? 0 : i + 1])) {
                    return true;
                }
            }
            else {
                // set INF
                const int INF = 1e9 + 10;
                P pp = P(INF, p.y);
                // 다각형이 꼭짓점을 지날 때 위쪽 변만 카운트
                if (segInter(A[i], A[i == n - 1 ? 0 : i + 1], p, pp) && (ccw(A[i], p, pp) == 1 || ccw(A[i == n - 1 ? 0 : i + 1], p, pp) == 1)) {
                    ++cnt;
                }
            }
        }
        return cnt & 1;
    }
    // 반시계 정렬 convex hull, O(lgn)
    friend bool pointInConvexPolygon(vector<P> &A, P p) {
        int n = sz(A);
        if (ccw(A[0], A[n - 1], p) == 1 || ccw(A[0], A[1], p) == -1) {
            return false;
        }
        int here = 0;
        for (int le = 1, ri = n - 1; le <= ri;) {
            int mid = (le + ri) / 2;
            if (ccw(A[0], A[mid], p) >= 0) {
                here = mid;
                le = mid + 1;
            }
            else {
                ri = mid - 1;
            }
        }
        assert(here != 0);
        if (ccw(A[0], A[here], p) == 0) {
            return min(A[0], A[here]) <= p && p <= max(A[0], A[here]);
        }
        return ccw(A[here], A[here == n - 1 ? 0 : here + 1], p) >= 0;
    }
    // 점 p에서 hull에 그은 접선
    // returns <leftmost idx, rightmost idx>
    friend pi tangent(vector<P> &A, int mx, P p) {
        int leftmost = 0, rightmost = 0;
        auto f = [&](P p, int lo, int hi, int dd, int &ret) {
            while (hi - lo > 3) {
                int le = (lo + lo + hi) / 3;
                int ri = (lo + hi + hi) / 3;
                int d = ccw(p, A[le], A[ri]);
                if (d == dd || (d == 0 && getDist2(p, A[ri]) < getDist2(p, A[le]))) {
                    lo = le;
                }
                else {
                    hi = ri;
                }
            }
            for (int i = lo; i <= hi; i++) {
                int d = ccw(p, A[ret], A[i]);
                if (d == dd || (d == 0 && getDist2(p, A[i]) < getDist2(p, A[ret]))) {
                    ret = i;
                }
            }
        };
        int n = sz(A);
        f(p, 0, mx, 1, leftmost);
        f(p, mx, n - 1, 1, leftmost);
        f(p, 0, mx, -1, rightmost);
        f(p, mx, n - 1, -1, rightmost);
        return pi(leftmost, rightmost);
    }
};

// // O = 원점
// // 4사분면(-y축 제외) -> 1사분면 -> 2사분면 -> 3사분면
// bool cmp(P l, P r) {
//     if (O < l != O < r) {
//         return l > r;
//     }
//     if (ccw(O, l, r) != 0) {
//         return ccw(O, l, r) == 1;
//     }
//     return getDist2(O, l) < getDist2(O, r);
// }

template<typename T>
struct point3 {
    using P = point3;
    T x, y, z;
    explicit point3(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {}
    bool operator<(P p) const { return tuple(x, y, z) < tuple(p.x, p.y, p.z); }
    bool operator<=(P p) const { return tuple(x, y, z) <= tuple(p.x, p.y, p.z); }
    bool operator>(P p) const { return tuple(x, y, z) > tuple(p.x, p.y, p.z); }
    bool operator>=(P p) const { return tuple(x, y, z) >= tuple(p.x, p.y, p.z); }
    bool operator==(P p) const { return tuple(x, y, z) == tuple(p.x, p.y, p.z); }
    P operator+(P p) const { return P(x + p.x, y + p.y, z + p.z); }
    P operator-(P p) const { return P(x - p.x, y - p.y, z - p.z); }
    P operator*(T d) const { return P(x * d, y * d, z * d); }
    P operator/(T d) const { return P(x / d, y / d, z / d); }
    // cross product
    P operator*(P p) const { return P(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x); }
    // dot product
    T dot(P p) const { return x * p.x + y * p.y + z * p.z; }
    T dist2() const { return x * x + y * y + z * z; }
    double dist() const { return sqrt(dist2()); }
    // Azimuthal angle (longitude) to x-axis in interval [-PI, PI]
    double phi() const { return atan2(y, x); }
    // Zenith angle (latitude) to the z-axis in interval [0, PI]
    double theta() const { return atan2(sqrt(x * x + y * y), z); }
    // makes dist() = 1
    P unit() const { return *this / T(dist()); }
    // returns unit vector normal to *this and p
    P normal(P p) const { return (*this * p).unit(); }
    // returns point rotated 'angle' radians ccw around axis
    P rotate(double angle, P axis) const {
        double s = sin(angle), c = cos(angle);
        P u = axis.unit();
        return u * dot(u) * (1 - c) + (*this) * c - (*this * u) * s;
    }
};