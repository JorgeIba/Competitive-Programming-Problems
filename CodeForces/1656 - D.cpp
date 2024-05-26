// Problem: D. K-good
// Contest: Codeforces - CodeTON Round 1 (Div. 1 + Div. 2, Rated, Prizes!)
// URL: https://codeforces.com/contest/1656/problem/D
// Memory Limit: 256 MB
// Time Limit: 3000 ms
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
	
	if(n % 2 == 1){
		cout << 2 << endl;
	} else {
		
		n *= 2;
		lli prod = 1;
		while(n % 2 == 0){
			n /= 2;
			prod *= 2;
		}
		if(n == 1) cout << -1 << endl;
		else {
			cout << min(prod, n) << endl;
		}
	}
	
}


int main () {
	//fastIO();
	
	int t = 1; cin>>t;
	while(t--) solve();


	return 0;
}

