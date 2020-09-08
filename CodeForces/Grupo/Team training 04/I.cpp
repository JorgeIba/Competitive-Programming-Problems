#include <bits/stdc++.h>
 
#define endl '\n'
#define fi first
#define se second
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define all(v) v.begin(), v.end()
#define pb push_back
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvll;
typedef vector<ll> vll;
typedef vector<pii> vpii;

int n,m;
vvi adj;
vi A, ans;

vi build(int u, set<int>& used, set<int>& disp){
	vi aux;
	aux.pb(u);
	used.insert(u);
	disp.erase(u);
	for(auto v:adj[u]){
		if(used.count(v)) continue;
		disp.insert(v);
	}
	while(disp.size() > 0){
		u = *disp.begin();
		aux.pb(u);
		used.insert(u);
		disp.erase(u);
		for(auto v:adj[u]){
			if(used.count(v)) continue;
			disp.insert(v);
		}
	}
	return aux;
}

bool solve(){
	vvi added(n);
//	vvi erased(n);
	set<int> used;
	set<int> disp;
	forn(i,n){
		used.insert(A[i]);
		for(auto v:adj[A[i]]){
			if(used.count(v) || disp.count(v)) continue;
			disp.insert(v);
			added[i].pb(v);
		}
//		cout << "added["<<i<<"]: "; for(auto j:added[i]) cout << j+1 << ' '; cout << endl;
	}
	disp.clear();
//	forn(i,n) used.insert(i);
	for(int i=n-1; i>=0; i--){
		disp.insert(A[i]);
		for(auto j:added[i]) disp.erase(j);
		used.erase(A[i]);
		//if(disp.size() == 1) continue;
//		cout << "erased["<<i<<"]: "; for(auto j:added[i]) cout << j+1 << ' '; cout << endl;
//		cout << "disp["<<i<<"]: "; for(auto j:disp) cout << j+1 << ' '; cout << endl;
		//auto it = disp.begin();
        auto it = disp.upper_bound(A[i]);
		//for(; it!=disp.end(); it++){
			//if(*it <= A[i]) continue;
			//break;
		//}
		if(it == disp.end()) continue;
		forn(j,i) ans.pb(A[j]);
		vi aux = build(*it,used,disp);
		for(auto j:aux) ans.pb(j);
		return true;
	}
	if(A[0] == n-1) return false;
	used.clear();
	disp.clear();
	ans = build(A[0]+1,used,disp);
	if(ans.size() == 0) return false;
	return true;
}

int main () {
	fastIO();
	cin >> n >> m;
	adj.resize(n);
	forn(i,m){
		int u,v;
		cin >> u >> v;
		u--; v--;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	A.resize(n);
	forn(i,n){
		cin >> A[i];
		A[i]--;
	}
	if(solve()){
		for(auto i:ans) cout << i+1 << ' ';
		cout << endl;
	}
	else cout << "-1\n";
	return 0;

}
