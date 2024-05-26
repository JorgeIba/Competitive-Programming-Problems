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

typedef long long lli;
typedef long double ld;
typedef pair<lli, lli> plli;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<lli>> vvlli;
typedef vector<lli> vlli;
typedef vector<pii> vpii;

const int MAXN = 1e6 + 5;
const int INF = 1e9;

int n;
vpii cities[MAXN];
vpii objects[MAXN];
lli mem[MAXN];
int idx[MAXN];

pii nxt(int c, int id){
	if(idx[id] + 1 >= SZ(objects[id])){
		idx[id]--;
		return {n + 1, -INF};
	}
	auto ans = objects[id][idx[id] + 1];
	idx[id]--;
	return ans;
	/* auto p = lower_bound(all(objects[id]), make_pair(c + 1, -1)); */
	/* if(p == objects[id].end()){ */
	/* 	return {n + 1, -INF}; */
	/* } */
	/* return *p; */
}

lli dp(int i){
	if(i >= n) return 0;
	lli& ans = mem[i];
	if(ans != -1) return ans;
	ans = 0;
	for(auto [id, p]:cities[i]){
		auto [j, np] = nxt(i, id);
		lli aux = -p + np + dp(j);
		/* cout << var(p) << ' ' << var(np) << endl; */
		/* cout << var(i) << ' ' << var(aux) << endl; */
		ans = max(ans, aux);
	}
	ans = max(ans, dp(i + 1));
	/* cout << var(i) << ' ' << var(ans) << endl; */
	return ans;
}

int main () {
	fastIO();
	memset(mem, -1, sizeof(mem));
	cin >> n;
	set<int> s;
	map<int,int> remap;
	vi v;
	forn(i, n){
		int m;
		cin >> m;
		forn(j, m){
			int id, p;
			cin >> id >> p;
			cities[i].pb({id, p});
			/* s.insert(id); */
			v.pb(id);
		}
	}
	sort(all(v));
	forn(i, SZ(v)){
		if(i > 0 && v[i] == v[i - 1]) continue;
		remap[v[i]] = remap.size();
	}
	/* for(auto i:s) */
	/* 	remap[i] = remap.size(); */
	forn(i, n){
		for(auto& [id, p]:cities[i]){
			id = remap[id];
			idx[id] = objects[id].size();
			objects[id].pb({i,p});
		}
	}
	for(int i = n; i >= 0; i--)
		dp(i);
	/* forn(i, n) for(auto [id,p]:cities[i]) cout << var(id) << endl; */
	cout << dp(0) << endl;
	return 0;
}

