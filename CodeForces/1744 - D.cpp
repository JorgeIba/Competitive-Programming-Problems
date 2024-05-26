// Problem: D. Divisibility by 2^n
// Contest: Codeforces - Codeforces Round  #828 (Div. 3)
// URL: https://codeforces.com/contest/1744/problem/D
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

lli getPot(lli x) {
	lli pot2 = 0;
	while(x % 2 == 0 && x > 0) {
		pot2++;
		x /= 2;
	}	
	return pot2;
}

void solve(){
	lli n; cin>>n;
	vector<lli> nums(n);
	
	for(auto &x: nums) cin>>x;
	
	lli pot2 = 0;
	for(auto x: nums) {
		pot2 += getPot(x);
	}
	
	if(pot2 >= n) {
		cout << 0 << endl;
		return;
	}
	
	
	vector<lli> options;
	for(int i = 2; i <= n; i += 2) {
		lli new_pot = getPot(i);
		options.push_back(new_pot);
	}
	
	sort(options.rbegin(), options.rend());
	
	lli ans = 0;
	for(auto x: options){
		ans++;
		pot2 += x;
		if(pot2 >= n){
			cout << ans << endl;
			return;
		}
	}
	
	
	
	cout << -1 << endl;
}


int main () {
	//fastIO();
	
	int t; cin>>t;
	while(t--) solve();

	return 0;
}

