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
const int mxn = 2e5+20;
int n, m;
vi path;
vi adj[mxn];
int c[mxn];
bool createPath(int u, int des, int p){
	if(u == des){
		path.pb(u);
		return true;
	}
	for(int v : adj[u]){
		if(v != p){
			if(createPath(v,des,u)){
				path.pb(u);
				return true;
			}
		}
	}
	return false;
}
vi bfs(int src){
	vi dis(n, -1);
	queue<int> q;
	q.push(src);
	dis[src] = 0;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(int v : adj[u]) if(dis[v] == -1){
			dis[v] = dis[u] + 1;
			q.push(v);
		}
	}
	return dis;
}
int main(){
	fastIO();
	cin >> n >> m;
	forn(i,n-1){
		int u, v;
		cin >> u >> v;
		u--; v--;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	forn(i,m) {
		cin >> c[i];
		c[i]--;
	}
	if(m == 1){
		cout << "YES\n";
		cout << c[0] + 1<< endl;
	}
	else{
		bool pos = 1;
		createPath(c[0], c[1], -1);
		if(SZ(path) & 1){
			int mid = path[(SZ(path)/2)];
			vi dis = bfs(mid);
			int ans = dis[c[0]];
			for(int i = 0; i < m; i++){
				assert(dis[c[i]] != 0 && dis[c[i]] != -1);
				if(dis[c[i]] != ans){
					pos = 0;
				}
			}
			if(pos){
				cout << "YES\n";
				cout << mid+1 << '\n';
			}
			else{	
				cout << "NO\n";
			}
		}
		else
			cout << "NO\n";
	}
	return 0;
}

