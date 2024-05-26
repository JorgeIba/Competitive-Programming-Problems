// Problem: B. Points on Plane
// Contest: Codeforces - Educational Codeforces Round 145 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1809/problem/B
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;


void main_(){
	lli n; cin>>n;
	if(n == 1) {
		cout << 0 << endl;
		return;
	}


	lli l = 1, r = 1e9+10, ans = r;
	while(l <= r) {
		lli mid = (l + r) / 2;
		if((mid+1)*(mid+1) >= n) {
			r = mid-1;
			ans = mid;
		} else {
			l = mid+1;
		}
	}
	cout << ans << endl;
}


int main () {
	//fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

