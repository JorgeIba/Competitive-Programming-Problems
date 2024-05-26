// Problem: C. Make Equal With Mod
// Contest: Codeforces - CodeTON Round 1 (Div. 1 + Div. 2, Rated, Prizes!)
// URL: https://codeforces.com/contest/1656/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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
	vector<lli> nums(n);
	for(auto &x: nums) cin>>x;
	
	int ones = count(all(nums), 1);
	
	if(!ones) {
		cout << "YES\n";
		return;
	}
	
	set<lli> check(all(nums));
	
	bool ans = true;
	for(auto x: nums) {
		if(x == 1) continue;
		if(check.count(x-1) || x-1 < 2) ans = false;
	}
	
	
	if(ans) cout << "YES\n";
	else cout << "NO\n";
	
}


int main () {
	//fastIO();
	
	int t = 1; cin>>t;
	while(t--) solve();


	return 0;
}

