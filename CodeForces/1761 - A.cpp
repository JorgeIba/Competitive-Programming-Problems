// Problem: A. Two Permutations
// Contest: Codeforces - Pinely Round 1 (Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/1761/problem/0
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

	int n, a, b; cin>>n>>a>>b;
	
	if(n == a && n == b){
		cout << "Yes\n";
	} else {
		if(a+b+2 <= n) {
			cout << "Yes\n";
		} else {
			cout << "No\n";
		}
	}
	
}


int main () {
	//fastIO();
	
	int t = 1; cin>>t;
	while(t--) solve();


	return 0;
}

