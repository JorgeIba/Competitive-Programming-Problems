#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef long long int lli;
typedef long double ld;


lli GaussI(lli n) {
    return n * (n+1) / 2;
}

lli Gauss(int l, int r) {
    return GaussI(r) - GaussI(l-1);
}


struct Node {

    int l = 0, r = 0;

    lli start = 0;
    lli V = 0;
    lli sum = 0;

    bool flagLazyStart = false;
    lli lazyStart = 0;

    bool flagLazyValue = false;
    lli lazyValue = 0;

    Node() {}
    Node(int l, int r, int start = 0) : l(l), r(r), start(start) {
        int L = start - r;
        int R = start - l;
        sum = V * Gauss(L, R);
    }


    // Combine 2 nodes
    Node operator+(const Node &b) {
        Node res(l, b.r);
        res.start = start;
        res.V = V;



        res.sum = sum + b.sum;
        return res;
    }

    // Update range
    void updateNode(int type, lli value) {
        int L = start - r;
        int R = start - l;

        if(type == 1) { // Range
            int L_new = value - r;
            int R_new = value - l;

            // sum += V * (Gauss(L_new, R_new) - Gauss(L, R));
        
            sum = V * Gauss(L_new, R_new);

            start = value;
            flagLazyStart = true;
            lazyStart = value;
        } else {

            sum = value * Gauss(L, R);

            V = value;
            flagLazyValue = true;
            lazyValue = value;
        }

        // cout << "Updated Node: " << l << " - " << r << " --> sum: " << sum << " --- type: " << type << " --- value: " << value << " --- start: " << start << " --- V: " << V << endl;
    }
};

// T Lo que le vas a pasar
template <typename T> struct SegmentTree {
    vector<Node> ST;
    int N;

    SegmentTree(int n) : N(n) {
        ST.resize(4 * N);
        build(1, 1, N);
    }

    void init_leaf(int curr, T value, int idx) {
        ST[curr] = Node(idx, idx, value);
    }

    void build(int curr, int l, int r) {
        ST[curr].l = l, ST[curr].r = r;
        if (l == r) {
            init_leaf(curr, N, l);
        } else {
            int mid = l + (r - l) / 2;
            build(2 * curr, l, mid);
            build(2 * curr + 1, mid + 1, r);
            ST[curr] = ST[2 * curr] + ST[2 * curr + 1];
        }
    }

    void pushToChildren(int curr) {
        if (ST[curr].flagLazyStart) {
            // cout << "FROM LAZY 1" << endl;
            ST[2 * curr].updateNode(1, ST[curr].lazyStart);
            ST[2 * curr + 1].updateNode(1, ST[curr].lazyStart);
            ST[curr].flagLazyStart = false;
            ST[curr].lazyStart = 0;
        }
        if (ST[curr].flagLazyValue) {
            // cout << "FROM LAZY 2" << endl;
            ST[2 * curr].updateNode(2, ST[curr].lazyValue);
            ST[2 * curr + 1].updateNode(2, ST[curr].lazyValue);
            ST[curr].flagLazyValue = false;
            ST[curr].lazyValue = 0;
        }
    }

    // UPDATE
    void update(int curr, int l, int r, int ql, int qr, int type, T value) {
        if (l > qr || r < ql)
            return;
        else if (ql <= l && r <= qr) {
            ST[curr].updateNode(type, value);
            return;
        }

        pushToChildren(curr);

        int mid = l + (r - l) / 2;
        update(2 * curr, l, mid, ql, qr, type, value);
        update(2 * curr + 1, mid + 1, r, ql, qr, type, value);

        ST[curr] = ST[2 * curr] + ST[2 * curr + 1];
    }
    void update(int ql, int qr, int type, T value) {
        if(ql > qr) return;
        update(1, 1, N, ql, qr, type, value);
    }

    // QUERY
    Node query(int curr, int l, int r, int ql, int qr) {
        if (l > qr || r < ql)
            return Node();
        else if (ql <= l && r <= qr)
            return ST[curr];
        else {
            pushToChildren(curr);
            int mid = l + (r - l) / 2;
            return query(2 * curr, l, mid, ql, qr) +
                   query(2 * curr + 1, mid + 1, r, ql, qr);
        }
    }
    Node query(int ql, int qr) { return query(1, 1, N, ql, qr); }



    void debugNode(Node curr) {
        cout << " --> " << curr.l << " - " << curr.r << " --> V: " << curr.V << " - start: " << curr.start << " - sum: " << curr.sum << " -- lazyStart: " << curr.lazyStart << " -- lazyValue: " << curr.lazyValue << endl;
    }
    void debugTree(int curr, int l, int r) {
        debugNode(ST[curr]);

        if(l == r) return;

        pushToChildren(curr);

        int mid = l + (r - l) / 2;
        debugTree(2 * curr, l, mid);
        debugTree(2 * curr + 1, mid + 1, r);
    }
};


int main () {
	fastIO();

    int n, m, q; cin>>n>>m>>q;

    vector<int> harbours_pos(m), harbours_val(m);
    for(auto &x: harbours_pos) {
        cin>>x;
        x--;
    }

    int val_l = 0;
    for(int i = 0; i < m; i++) {
        cin >> harbours_val[i];
        if(harbours_pos[i] == 0) {
            val_l = harbours_val[i];
        }
    }

    vector<int> values(n);
    for(int i = 0; i < m; i++) {
        values[harbours_pos[i]] = harbours_val[i];
    }

    set<int> pos(all(harbours_pos));
    auto find_prev = [&](int idx) {
        auto itr = pos.lower_bound(idx);
        itr--;
        return *itr;
    };

    auto find_next = [&](int idx) {
        auto itr = pos.upper_bound(idx);
        return *itr;
    };

    SegmentTree<lli> ST(n);

    ST.update(1, n, 1, n);
    ST.update(2, n-1, 2, val_l);
    ST.update(1, 1, 1, 1);

    auto insert_harbour = [&](int pos, lli val) {
        int l = find_prev(pos);
        int r = find_next(pos);

        ST.update(l+1+1, pos+1, 1, pos+1);
        ST.update(pos+1+1, r+1-1, 2, val);
    };

    for(int i = 0; i < m; i++) {
        int y = harbours_pos[i];
        if(y == 0 || y == n-1) continue;
        
        insert_harbour(y, values[y]);
    }

    while(q--){
        int t, a, b; cin>>t>>a>>b;

        if(t == 1) {
            insert_harbour(a-1, b);

        } else {

            if(a == 99692 && b == 99790) {
                lli ans = 0;
                for(int i = a; i <= b; i++) {
                    ans += ST.query(i,i).sum;
                }
                cout << ans << endl;
            }

            cout << ST.query(a, b).sum << endl;
        }
    }

	return 0;
}

