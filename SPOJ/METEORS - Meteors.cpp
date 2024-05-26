#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)
#define pb push_back
#define fi first
#define se second

using namespace std;

const int MAXN = 3e5 + 100;
namespace bit {
	lli bit[2][MAXN+2];
	int n;

	void build(int n2) {
		n = n2;

		for(int i = 0; i < 2; i++){
            for(int j = 0; j <= n+20; j++)
                bit[i][j] = 0;
        }
	}
	lli get(int x, int i) {
		lli ret = 0;
		for (; i; i -= i&-i) ret += bit[x][i];
		return ret;
	}
	void add(int x, int i, lli val) {
		for (; i <= n; i += i&-i) bit[x][i] += val;
	}
	lli get2(int p) {
		return get(0, p) * p + get(1, p);
	}
	lli query(int l, int r) {
		return get2(r+1) - get2(l);
	}
	void update(int l, int r, lli x) {
		add(0, l+1, x), add(0, r+2, -x);
		add(1, l+1, -x*l), add(1, r+2, x*(r+1));
	}
};



vector<int> adjList[MAXN];
vector< int > queries_on_upd[MAXN];
pair<int,int> queries[MAXN];
tuple<int,int,int> updates[MAXN];
int total_ans[MAXN];
int needs[MAXN];

int main () {
	fastIO();
	
    int n, m; cin>>n>>m;

    forr (i, 1, m) {
        int own; cin>>own;
        adjList[own].pb(i);
    }

    forr (i, 1, n) {
        cin>>needs[i];
    }    


    int q; cin>>q;
    forr(i, 1, q) {
        int l, r, k; cin>>l>>r>>k;
        updates[i] = {l, r, k};
    }


    int mid = (q+1)/2;
    forr(i, 1, n) {
        queries[i] = {1, q};
        queries_on_upd[mid].push_back(i);
    }

    forr(i, 1, n) total_ans[i] = -1;

    for(int rep = 0; rep < 20; rep++) {
        bit::build(m+10);

        auto update_tree = [&](int l, int r, int k) {
            if(l <= r) {
                bit::update(l, r, k);
            } else {
                bit::update(l, m, k);
                bit::update(1, r, k);
            }
        };

        vector<bool> ans_mid(n+1);
        forr(i, 1, q) {
            auto &[l, r, k] = updates[i];
            update_tree(l, r, k);

            for(auto idx: queries_on_upd[i]) {
                lli total_gathered = 0;
                for(auto v: adjList[idx]) {
                    if(total_gathered >= needs[idx]) break;

                    total_gathered += bit::query(v,v);
                }

                ans_mid[idx] = (total_gathered >= needs[idx]);
            }
        }

        forr(i, 1, q) queries_on_upd[i].clear();

        forr(i, 1, n){
            auto &[l, r] = queries[i];
            int mid = (l + r)/2;
            if(ans_mid[i]) {
                total_ans[i] = mid;
                r = mid-1;
            } else {
                l = mid+1;
            }
            int new_mid = (l + r) / 2;
            
            if(new_mid < 1 || new_mid > q) continue;
        
            assert(1 <= new_mid && new_mid <= q);
            queries_on_upd[  new_mid  ].push_back(i);
        }
    }


    forr(i, 1, n){
        if(total_ans[i] == -1) {
            cout << "NIE" << endl;
        } else {
            cout << total_ans[i] << endl;
        }
    }
        

	return 0;
}

