struct Line {
    int a, b;
    Line(int a = 0, int b = minf) : a(a), b(b) {}
    int get(int x) {
        return a * x + b;
    }
};

struct Lichao {
    int st, en, size, x;
    Line val;
    Line node[20 * MAXN];
    int chd[20 * MAXN][2];

    void init(int st, int en) {
        this->st = st, this->en = en;
        size = 1;
        node[0] = Line();
    }

    void add(Line val) {
        this->val = val;
        update(0, st, en);
    }

    void update(int nidx, int st, int en) {
        Line lo = node[nidx];
        Line hi = val;
        if (hi.get(st) < lo.get(st)) {
            swap(lo, hi);
        }
        if (lo.get(en) <= hi.get(en)) {
            node[nidx] = hi;
            return;
        }
        int mid = (st + en) >> 1;
        // 교점 오른쪽
        if (lo.get(mid) < hi.get(mid)) {
            node[nidx] = hi;
            val = lo;
            if (chd[nidx][1] == 0) {
                chd[nidx][1] = size++;
                node[size - 1] = Line();
            }
            int ridx = chd[nidx][1];
            update(ridx, mid + 1, en);
        }
        // 교점 왼쪽
        else {
            node[nidx] = lo;
            val = hi;
            if (chd[nidx][0] == 0) {
                chd[nidx][0] = size++;
                node[size - 1] = Line();
            }
            int lidx = chd[nidx][0];
            update(lidx, st, mid);
        }
    }

    int solve(int x) {
        this->x = x;
        return solve(0, st, en);
    }

    int solve(int nidx, int st, int en) {
        int ret = node[nidx].get(x);
        int mid = (st + en) >> 1;
        if (x <= mid) {
            int lidx = chd[nidx][0];
            if (lidx) {
                ret = max(ret, solve(lidx, st, mid));
            }
        }
        else {
            int ridx = chd[nidx][1];
            if (ridx) {
                ret = max(ret, solve(ridx, mid + 1, en));
            }
        }
        return ret;
    }
} seg;