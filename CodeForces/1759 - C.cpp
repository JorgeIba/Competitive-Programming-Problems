// Problem: C. Thermostat
// Contest: Codeforces - Codeforces Round  #834 (Div. 3)
// URL: https://codeforces.com/contest/1759/problem/C
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


const lli INF = 1e18;
lli dfs(lli l, lli r, lli a, lli b, lli x, lli tryye) {
	if(abs(a-b) >= x) return 1;
	if(abs(a-b) == 0) return 0;
	if(tryye > 5) return INF;
	
	
	lli ans = INF;
	if(a != l && abs(a-l) >= x){
		ans = min(ans, 1 + dfs(l, r, l, b, x, tryye+1));
	}
	
	if(a != r && abs(a-r) >= x) {
		ans = min(ans, 1 + dfs(l, r, r, b, x, tryye+1));
	}
	
	return ans;
}


void solve() {
	
	lli l, r, x; cin>>l>>r>>x;
	
	lli a, b; cin>>a>>b;
	
	if(a == b) {
		cout << 0 << endl;
		return;
	}
	
	lli ans = dfs(l, r, a, b, x, 0);
	
	if(ans == INF) cout << -1 << endl;
	else cout << ans << endl;


}



int main () {
	//fastIO();
	int t; cin>>t;
	
	while(t--) solve();

	return 0;
}

