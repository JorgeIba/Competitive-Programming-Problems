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

struct DSU {
    int n;
    vector< pair<int,int> > parent;
    vector<int> sz;
    int comps;
    bool is_valid = true;

    DSU(int n): n(n), parent(n), sz(n, 1), comps(n) {
        forn(i, n)
            parent[i] = {i, 0};
    }

    pair<int,int> root(int u) {
        auto [p, dup] = parent[u];
        if(p == u) return parent[u];

        auto [r, dpr] = root(p);

        return {r, dup ^ dpr};
    }


    void join(int u, int v, int w) {
        auto [Ru, Du] = root(u);
        auto [Rv, Dv] = root(v);
        if(Ru == Rv) {
            if((Du^Dv) != w) is_valid = false;
            return;
        }

        if(sz[Ru] < sz[Rv]) {
            swap(Ru, Rv);
            swap(Du, Dv);
        }

        parent[Rv] = {Ru, Du ^ w ^ Dv};
        sz[Ru] += sz[Rv];
        comps--;
    }
};

const int MAXN = 2e5 + 100;
const int MOD = 1e9+7;

int pows[MAXN];

void main_() {
    int n, m, k, q; cin>>n>>m>>k>>q;
    DSU D(n + m);

    forn(i, k) {
        int r, c, v; cin>>r>>c>>v;
        r--, c--;
        D.join(r, n + c, v);
    }

    auto print_ans = [&]() {
        cout << (D.is_valid ? pows[D.comps-1] : 0) << endl;
    };

    print_ans();
    forn(test, q) {
        int r, c, v; cin>>r>>c>>v;
        r--, c--;
        D.join(r, n + c, v);

        print_ans();
    }
}

int main () {
	fastIO();

    pows[0] = 1;
    forr(i, 1, MAXN-1) {
        pows[i] = (1LL << 30) * pows[i-1] % MOD;
    }

	int t = 1;
	cin>>t;

	while(t--) {
		main_();
	}


	return 0;
}

