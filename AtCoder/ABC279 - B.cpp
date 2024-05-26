// Problem: B - LOOKUP
// Contest: AtCoder - TOYOTA SYSTEMS Programming Contest 2022(AtCoder Beginner Contest 279)
// URL: https://atcoder.jp/contests/abc279/tasks/abc279_b
// Memory Limit: 1024 MB
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

void main_(){
	string s, t; cin>>s>>t;
	
	if(s.find(t) != std::string::npos) {
		cout << "Yes\n";
	} else {
		cout << "No\n";
	}
	
}


int main () {
	//fastIO();
	
	int t = 1; 
	while(t--) 
		main_();


	return 0;
}

