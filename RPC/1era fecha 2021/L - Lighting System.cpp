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
const int mxn = (int)1e4+20;
vi adj[mxn];
bool vis[mxn];
int dfs(int u){
	vis[u] = 1;
	int ret = 1;
	for(int v : adj[u]){
		if(!vis[v])
			ret += dfs(v);
	}
	return ret;
}
int main(){
	fastIO();
	int n, p;
	while(cin >> n >> p){
		forn(i,n){
			vis[i] = 0;
			adj[i].clear();
		}
		forn(i,p){
			int u, v;
			cin >> u >> v;
			u--; v--;
			adj[u].pb(v);
			adj[v].pb(u);
		}
		forn(i,n){
			if(!vis[i]){
				int aux = dfs(i);
				cout << (i+1) << ' ' << aux << '\n';
			}
		}
	}
	return 0;
}

