// Problem: B. Three Sevens
// Contest: Codeforces - Codeforces Round 860 (Div. 2)
// URL: https://codeforces.com/contest/1798/problem/B
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
	int n; cin>>n;
	
	map<int,int> last;
	
	forn(i, n) {
		int m; cin>>m;
		forn(j, m) {
			int x; cin>>x;
			last[x] = i;
		}
	}
	
	
	vector<int> day(n, -1);
	for(auto [x, d]: last) {
		day[d] = x;
//		cout << d << " -- " << x << endl;
	}
	
	for(auto x: day) {
		if(x == -1) {
			cout << -1 << endl;
			return;
		}
	}
	
	for(auto x: day) cout << x << " ";
	cout << endl;
	
}


int main () {
	//fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

