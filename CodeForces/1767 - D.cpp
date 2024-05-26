// Problem: D. Playoff
// Contest: Codeforces - Educational Codeforces Round 140 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1767/problem/D
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

using namespace std;


int main () {
	//fastIO();
	
	lli n; cin>>n;
	string s; cin>>s;
	bitset<20> s_bitset(s);
	
	lli c = s_bitset.count();
	lli b = n - c;
	
	lli lower_limit = (1LL<<(c));
	lli upper_limit = (1LL << n) - (1LL << b) + 1;

//	cout << upper_limit << endl;
	
	for(int i = lower_limit; i <= upper_limit; i++){
		cout << i << " ";
	}
	cout << endl;


	return 0;
}

