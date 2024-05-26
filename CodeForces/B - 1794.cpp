// Problem: B. Not Dividing
// Contest: Codeforces - Codeforces Round 856 (Div. 2)
// URL: https://codeforces.com/contest/1794/problem/B
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


void solve(){
	int n; cin>>n;
	vector< int > nums(n);
	for(auto &x: nums) {
		cin>>x;
	}
	
	for(auto &x: nums){
		if( x == 1 ) x++;
	}
	
	
	for(int i = 1; i < n; i++){
		if(nums[i] % nums[i-1] == 0) nums[i]++;
	}
	
	for(auto x: nums) cout << x << " ";
	cout << endl;
	
}

int main () {
	//fastIO();
			

	int t; cin>>t;
	while(t--) solve();



	return 0;
}

