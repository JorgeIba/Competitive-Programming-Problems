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


void main_(){
	int n; cin>>n;	
	vector<lli> nums(n+1);
	for(int i = 1; i <= n; i++)	
		cin>>nums[i];

	
	vector< vector<int> > cycles;
	vector<int> visited(n+1); // 

	auto dfs = [&](const auto &dfs, int u, vector<int> &cycle) {
		if(visited[u] == 1){
			reverse(all(cycle));
			while(cycle.back() != u) cycle.pop_back();

			cycles.push_back(cycle);
			return;
		}
		if(visited[u] == 2) return;

		visited[u] = 1;
		cycle.push_back(u);

		dfs(dfs, nums[u], cycle);
	
		visited[u] = 2;
	};


	for(int i = 1; i <= n; i++) {
		if(visited[i]) continue;
		vector<int> cycle;
		dfs(dfs, i, cycle);
	}

	lli ans = 0;
	for(auto c: cycles){
		ans += SZ(c);
		// cout << "CYCLE: ";
		// for(auto x: c) cout << x << " ";
		// cout << endl;
	}

	cout << ans << endl;
}


int main () {
	//fastIO();
	
	int t = 1;
//	cin>>t;
	
	while(t--) main_();


	return 0;
}

