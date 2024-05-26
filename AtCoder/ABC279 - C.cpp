// Problem: C - RANDOM
// Contest: AtCoder - TOYOTA SYSTEMS Programming Contest 2022(AtCoder Beginner Contest 279)
// URL: https://atcoder.jp/contests/abc279/tasks/abc279_c
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
	int r, c; cin>>r>>c;
	
	vector<string> S(r);
	for(auto &x: S) cin>>x;
	
	vector<string> W(r);
	for(auto &x: W) cin>>x;
	
	
	vector<string> colsS;
	for(int i = 0; i < c; i++) {
		string col;
		for(int j = 0; j < r; j++) {
			col.push_back(S[j][i]);
		}
		colsS.push_back(col);
	}
	
	
	vector<string> colsW;
	for(int i = 0; i < c; i++) {
		string col;
		for(int j = 0; j < r; j++) {
			col.push_back(W[j][i]);
		}
		colsW.push_back(col);
	}
	
	sort(all(colsS));
	sort(all(colsW));
	
	if(colsS == colsW) {
		cout << "Yes\n";
	} else {
		cout << "No\n";
	}
	
}


int main () {
	//fastIO();
	
	int t = 1; 
//	cin>>t;
	while(t--) 
		main_();


	return 0;
}

