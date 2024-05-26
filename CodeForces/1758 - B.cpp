// Problem: B. XOR = Average
// Contest: Codeforces - Codeforces Round #836 (Div. 2)
// URL: https://codeforces.com/contest/1758/problem/B
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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
	lli n; cin>>n;
	
	if( n % 2 == 1 ){
		for(int i = 1; i <= n; i++) cout << n << " ";
		cout << endl;
	} else {
		cout << 1 << " " << 3 << " ";
		for(int i = 3; i <= n; i++) cout << 2 << " ";
		cout << endl;
	}
	
}


int main () {
	//fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

