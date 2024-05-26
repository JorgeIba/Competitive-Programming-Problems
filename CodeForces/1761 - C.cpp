// Problem: C. Set Construction
// Contest: Codeforces - Pinely Round 1 (Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/1761/problem/C
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


void solve(){
	lli n; cin>>n;
	
	vector<string> mat(n);
	for(auto &s: mat) cin>>s;
	
	vector<vector<lli>> adjList(n);
	vector<lli> income(n);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++) {
			if(mat[i][j] == '1') {
				adjList[i].push_back(j);
				income[j]++;
			}
		}
	}
	

	queue<lli> q;
	
	for(int i = 0; i < n; i++) {
		if(income[i] == 0) {
			q.push(i);

		}
	}
	
	
	
	vector<vector<lli>> ans(n);
	while(!q.empty()) {
		auto u = q.front(); q.pop();
		ans[u].push_back(u);
		
		for(auto v: adjList[u]) {
			ans[v].push_back(u);
			
			income[v]--;
			if(!income[v]){
				q.push(v);
			}
			
		}
	}

	
	for(auto a: ans){
		cout << SZ(a) << " ";
		for(auto x: a) cout << x+1 << " ";
		cout << endl;
	}
	
	
	
}


int main () {
	//fastIO();
	
	int t = 1; cin>>t;
	while(t--) solve();


	return 0;
}

