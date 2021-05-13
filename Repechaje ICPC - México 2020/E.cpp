#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,n) for(int i = a; i <= n; i++)
#define all(v) v.begin(), v.end()
#define se second
#define fi first
#define pb push_back
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
 
using namespace std; 

typedef pair<lli, lli> plli;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<lli>> vvlli;
typedef vector<lli> vlli;
typedef vector<pii> vpii;
const int MAXN = 1e6+10;
vi adj[MAXN];
pair<int,int> sum[MAXN];
int pa[MAXN], boss;
lli ans[MAXN];
void dfs1(int u){
	ans[u] = sum[u].fi + sum[u].se;
	for(int v : adj[u]) if(pa[u] != v){
		dfs1(v);
		ans[u] += ans[v];
	}
}
lli dfs2(int u){
	for(int v : adj[u]) if(pa[u] != v){
		sum[u].se += dfs2(v);
	}
	return sum[u].se;
}
int main(){
	fastIO();
	int n, m, q;
	cin >> n >> m >> q;
	forn(i,n) {
		int x;
		cin >> x;
		x--;
		if(x != -1){
			adj[x].pb(i);
			adj[i].pb(x);
		}
		else boss = i;
		pa[i] = x;
	}
	forn(i,m){
		int op, u, val;
		cin >> op >> u >> val;
		u--;
		if(op == 1) sum[u].fi += val;
		else sum[u].se += val;
	}
	dfs2(boss);
	dfs1(boss);
	forn(i,q){
		int opc, u;
		cin >> opc >> u;
		u--;
		if(opc == 1) cout << sum[u].fi + sum[u].se << '\n';
		else cout << ans[u] << '\n';
	}
	return 0;
}

