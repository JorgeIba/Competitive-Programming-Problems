// Problem: E1. Divisible Numbers (easy version)
// Contest: Codeforces - Codeforces Round  #828 (Div. 3)
// URL: https://codeforces.com/contest/1744/problem/E1
// Memory Limit: 256 MB
// Time Limit: 4000 ms
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


// L < k*num <= R
lli sol(lli L, lli R, lli num) {
	lli L_aux = L/num, R_aux = R/num;
	
	for(lli k = L_aux; k <= R_aux; k++) {
		if( L < k*num && k*num <= R) {
			return k*num;
		}
	} 
	return -1;
}

void solve(){
	lli a, b, c, d; cin>>a>>b>>c>>d;
	
	lli Lx = a, Rx = c;
	lli Ly = b, Ry = d;
		
	
	lli den = a*b;
	for(lli x = Lx+1; x <= Rx; x++){
		lli gcd = __gcd(x, den);
		lli num = den/gcd;
		
		// cout << Lx << " - " << x << " - " << Rx << " ";
		// cout << num << endl;
		
		lli y = sol(Ly, Ry, num);
		if(y == -1) continue;	
		else {
			cout << x << " " << y << endl;
			return;
		}
	}
	
	cout << -1 << " " << -1 << endl;
		
}


int main () {
	//fastIO();
	lli t; cin>>t;
	
	while(t--) solve();

	return 0;
}

