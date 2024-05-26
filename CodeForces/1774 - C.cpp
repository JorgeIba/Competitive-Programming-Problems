// Problem: C. Ice and Fire
// Contest: Codeforces - Polynomial Round 2022 (Div. 1 + Div. 2, Rated, Prizes!)
// URL: https://codeforces.com/contest/1774/problem/C
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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

void main_(){
	int n; cin>>n;
	string s; cin>>s;
	
	char last = '2';
	int how_many = 0;
	for(int i = 0; i < SZ(s); i++){
		if(s[i] == last) {
			how_many++;
			
		} else {
			how_many = 1;
			last = s[i];			
		}
		cout << (i+2) - how_many << " ";
	}
	cout << endl;
}


int main () {
	//fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

