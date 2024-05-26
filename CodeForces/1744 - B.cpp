// Problem: B. Even-Odd Increments
// Contest: Codeforces - Codeforces Round  #828 (Div. 3)
// URL: https://codeforces.com/contest/1744/problem/B
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
	lli n, q; cin>>n>>q;
	
	lli s_odd = 0, s_even = 0, sz_odd = 0, sz_even = 0;
	for(int i = 0; i < n; i++){
		lli x; cin>>x;
		if(x % 2 == 0) s_even += x, sz_even++;
		else s_odd += x, sz_odd++;
	}
	
	
	while(q--){
		lli t, x; cin>>t>>x;
		
		if(t == 0){
				if(x % 2 == 0) {
					s_even += x*sz_even;
				} 
				else {
					s_odd += s_even + x*sz_even;
					sz_odd += sz_even;
					s_even = 0;
					sz_even = 0;
				}
		} else {
				if(x % 2 == 0){
					 s_odd += x*sz_odd;
				}
				else {
					s_even += s_odd + x*sz_odd;
					sz_even += sz_odd;
					s_odd = 0;
					sz_odd = 0;
				}			
		}
		cout << s_even + s_odd << endl;
	}
	
}



int main () {
	//fastIO();

	int t; cin>>t;
	
	while(t--) solve();
	return 0;
}

