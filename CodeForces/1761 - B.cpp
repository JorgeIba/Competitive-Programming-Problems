// Problem: B. Elimination of a Ring
// Contest: Codeforces - Pinely Round 1 (Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/1761/problem/B
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
	int n; cin>>n;
	vector<lli> nums(n);
	for(auto &x: nums) cin>>x;
	
	
	set<lli> distincts(all(nums));
	
	if(SZ(distincts) > 2) cout << n << endl;
	else {
		cout << n/2 + 1 << endl;
	}
	
}


int main () {
	//fastIO();
	
	int t = 1; cin>>t;
	while(t--) solve();


	return 0;
}

