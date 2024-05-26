// Problem: B. Incinerate
// Contest: Codeforces - Codeforces Round #840 (Div. 2) and Enigma 2022 - Cybros LNMIIT
// URL: https://codeforces.com/contest/1763/problem/B
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
	int n, k; cin>>n>>k;
	vector< array<lli, 2> > enemies(n);
	
	for(auto &v: enemies) cin>>v[0];
	for(auto &v: enemies) cin>>v[1];
	
	
	sort(all(enemies));
	
	
	vector<lli> suffix(n+1, 1e9);
	for(int i = n-1; i >= 0; i--){
		suffix[i] = min(suffix[i+1], enemies[i][1]);
	}
	

	lli total_damage = 0;
	lli idx = 0;
	
	while(idx < n && k > 0) {
		total_damage += k;
		while(idx < n && total_damage >= enemies[idx][0]) idx++;
		
		lli rest = 0;
		if(idx < n) rest = suffix[idx];
		
		k -= rest;
	}
	
	if(idx == n){
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
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

