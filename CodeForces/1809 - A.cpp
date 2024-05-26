// Problem: A. Garland
// Contest: Codeforces - Educational Codeforces Round 145 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1809/problem/0
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
	string s; cin>>s;
	vector<int> a;
	for(auto c: s) a.push_back(c - '0');
	
	map<int,int> fr;
	for(auto c: a) fr[c]++;
	
	
	if(SZ(fr) == 1) {
		cout << -1 << endl;
		return;
	} else if(SZ(fr) == 4 || SZ(fr) == 3) {
		cout << 4 << endl;
		return;
	} else {
		for(auto [x, f]: fr) {
			if(f == 1) {
				cout << 6 << endl;
				return;
			}
		}
		
		cout << 4 << endl;
		return;
		
	}

		
		
}


int main () {
	//fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

