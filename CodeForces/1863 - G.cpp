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

using namespace std;


const int MOD = 1e9+7;

int main () {
	fastIO();

	int n; cin>>n;
	vector<int> perm(n+1);

	forr(i, 1, n) cin>>perm[i];

	vector<int> income(n+1);
	forr(i, 1, n)
		income[perm[i]]++;


	vector<int> colors(n+1, 0), in_cycle(n+1, 0), sz_cycle(n+1, 0);
	vector<int> cycles_start;
	auto dfs = [&](const auto &dfs, int u, int color) -> void {
		if(colors[u] == color){
			cycles_start.push_back(u);
			return;
		} else if(colors[u] != 0) return;

		colors[u] = color;

		dfs(dfs, perm[u], color);
	};

	auto dfs_mark = [&](const auto &dfs_mark, int u, int &incoming_all, int &incoming_bad) -> void {

		if(in_cycle[u]) return;

		incoming_all = 1LL * incoming_all * (income[u] + 1) % MOD;
		incoming_bad += income[u];
		if(incoming_bad >= MOD) incoming_bad -= MOD;

		in_cycle[u] = 1;
		dfs_mark(dfs_mark, perm[u], incoming_all, incoming_bad);
	};


	int color = 1;
	forr(i, 1, n){
		if(colors[i] != 0) continue;
		dfs(dfs, i, color++);
	}


	vector<int> cycles_part;
	for(auto c: cycles_start){
		int incoming_all = 1;
		int incoming_bad = 0;
		dfs_mark(dfs_mark, c, incoming_all, incoming_bad);
		cycles_part.push_back((incoming_all - incoming_bad + MOD) % MOD);
	}

	int ans = 1;
	forr(i, 1, n){
		if(in_cycle[i]) continue;
		ans = 1LL * ans * (income[i] + 1) % MOD;
	}


	// debugg(ans);
	for(auto contribution: cycles_part){
		// debugg(contribution);
		ans = 1LL * ans * contribution % MOD;
	}

	cout << ans << endl;

	

	return 0;
}

