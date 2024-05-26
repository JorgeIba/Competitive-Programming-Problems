#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

typedef pair<lli,lli> pairr;

const lli INF = 1e15;
const int MIN_DOM = -1e9;
const int MAX_DOM = 1e9;

template<lli MI = MIN_DOM, lli MA = MAX_DOM> struct LiChaoTree {
	struct line {
		lli a, b;
		array<int, 2> ch;
		line(lli a_ = 0, lli b_ = INF) :
			a(a_), b(b_), ch({-1, -1}) {}
		lli operator ()(lli x) { return a*x + b; }
	};
	vector<line> ln;
	int sz = 0;
	stack<stack<pair<line&, line>>> st;

	void save(line &x) { st.top().emplace(x, x); }

	void checkpoint() { st.emplace(); }
	
	void rollback() {
		while(st.top().size()) {
			auto [end, val] = st.top().top(); st.top().pop();
			end = val;
		}
		st.pop();
	}

	int ch(int p, int d) {
		if (ln[p].ch[d] == -1) {
			ln[p].ch[d] = sz++;
			//ln.emplace_back();
		}
		return ln[p].ch[d];
	}
	LiChaoTree(int n) { ln.resize(4*n); st.emplace(); }

	void add(line s, lli l=MI, lli r=MA, int p=0) {
		lli m = (l+r)/2;
		bool L = s(l) < ln[p](l);
		bool M = s(m) < ln[p](m);
		bool R = s(r) < ln[p](r);
		save(ln[p]);
		if (M) swap(ln[p], s), swap(ln[p].ch, s.ch);
		if (s.b == INF) return;
		if (L != M) add(s, l, m-1, ch(p, 0));
		else if (R != M) add(s, m+1, r, ch(p, 1));
	}
	lli query(int x, lli l=MI, lli r=MA, int p=0) {
		lli m = (l+r)/2, ret = ln[p](x);
		if (ret == INF) return ret;
		if (x < m) return min(ret, query(x, l, m-1, ch(p, 0)));
		return min(ret, query(x, m+1, r, ch(p, 1)));
	}
};


const int maxN = 1e5+1000;

vector<lli> start(maxN), vel(maxN), prefix(maxN), parent(maxN);
vector< vector< pairr > > adjList(maxN);

LiChaoTree<> *LCH = new LiChaoTree<>(maxN);

void dfs_prec(int u, int p = -1){
    for(auto [v, w]: adjList[u]){
        if(v == p) continue;
        prefix[v] = prefix[u] + w;
        parent[v] = u;
        dfs_prec(v, u);
    }
}

int n;
lli dp[maxN];

void dfs_dp(int u, int p = -1){

    LCH->checkpoint();

    if(u != 1) {

        lli aux = LCH->query(vel[u]);
        lli ans = start[u] + prefix[u]*vel[u] + aux;
        dp[u] = ans;


        LCH->add({-prefix[u], dp[u]});
    }

    for(auto [v, w]: adjList[u]){
        if(v == p) continue;
        dfs_dp(v, u);
    }

    LCH->rollback();
}



int main () {
	fastIO();
    cin>>n;


    for(int i = 0; i < n-1; i++){
        int u, v, w; cin>>u>>v>>w;
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w});
    }

    for(int i = 2; i <= n; i++){
        cin>>start[i]>>vel[i];
    }

    dfs_prec(1);

    LCH->add({0, 0});

    dfs_dp(1, 0);

    for(int i = 2; i <= n; i++) cout << dp[i] << " ";

	return 0;
}

