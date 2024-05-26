// Problem: B. Diverse Substrings
// Contest: Codeforces - Codeforces Round #833 (Div. 2)
// URL: https://codeforces.com/contest/1748/problem/B
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


void solve() {
	lli n; cin>>n;
	string s; cin>>s;
	
	lli ans = 0;
	for(lli i = 0; i < n; i++) {
		map<lli,lli> fr;
		lli limit = min(n-1, i+105);
		for(int j = i; j <= limit; j++) {
			fr[s[j]]++;
			
			lli maxi = -1;
			for(auto [x, y]: fr) {
				maxi = max(maxi, y);
			}
			
			if(maxi <= SZ(fr)) {
				ans++;
			}
		
		}
	}
	cout << ans << endl;

}


int main () {
	//fastIO();
	int t; cin>>t;
	while(t--) solve();

	return 0;
}

