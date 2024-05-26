// Problem: B. Notepad#
// Contest: Codeforces - Educational Codeforces Round 139 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1766/problem/B
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
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

void main_(){
	int n; cin>>n;
	string s; cin>>s;
	
	if(n <= 2) {
		cout << "NO" << endl;
		return;
	}
	
	
	map<string, int> fr, fr2;

	string sub = s.substr(0, 2);
	
	string ret = sub;
	for(int i = 2; i < n; i++) {
		string sub = s.substr(i-1, 2);

		if(fr[sub] > 0) {
			cout << "YES" << endl;
			return;
		}
		
		
		fr[ret]++;
		ret = sub;
	}
	
	
	
	cout << "NO" << endl;
}


int main () {
	//fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

