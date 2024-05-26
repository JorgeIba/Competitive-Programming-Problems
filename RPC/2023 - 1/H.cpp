#include <bits/stdc++.h>

#define endl '\n'
#define fi first
#define se second
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define all(v) v.begin(), v.end()
#define pb push_back
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define var(x) #x << " = " << x

using namespace std;

typedef __int128 lli;
typedef long double ld;
typedef pair<lli, lli> plli;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<lli>> vvlli;
typedef vector<lli> vlli;
typedef vector<pii> vpii;
typedef tuple<lli,lli,lli>  tiii;

const int MAXN =3e5 + 5;

int n, q;
vi adj[MAXN];

void dfs(int u, lli a, lli b, vector<tiii>& nodes){
	if(adj[u].empty())
		nodes.pb({a, b, u});
	for(auto v:adj[u]){
		lli nb = b;
		if(nb < q)
			nb = b * SZ(adj[u]);
		if(a > q) break;
		dfs(v, a, nb, nodes);
		a += b;
	}
}

int main () {
	fastIO();
	cin >> n >> q;
	forn(i, n - 1){
		int p;
		cin >> p;
		adj[p].pb(i + 1);
	}
	vector<tiii> nodes;
	vi ans(q);
	dfs(0, 1, 1, nodes);
	for(auto t:nodes){
		lli a, b, u, k;
		k = 0;
		tie(a, b, u) = t;
		/* cout << var(a) << ' ' << var(b) << ' ' << var(u) << endl; */
		while((a + b * k) <= q){
			ans[a + b * k - 1] = u;
			k++;
		}
	}
	for(auto i:ans) cout << i << endl;
	return 0;
}

