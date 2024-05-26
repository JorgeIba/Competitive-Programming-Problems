// Problem: C. Bon appetit!
// Contest: Codeforces - Codeforces Round #846 (Div. 2)
// URL: https://codeforces.com/contest/1780/problem/C
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
	int n, m; cin>>n>>m;
	
	vector<lli> nums(n);
	map<lli,lli> fr;
	for(auto &x: nums) {
		cin>>x;
		fr[x]++;
	}
	
	vector< lli> tables(m);
	for(auto &x: tables) cin>>x;
	
	
	priority_queue< pair<lli,lli> > pq_weyes;
	priority_queue< pair<lli,lli> > pq_tables;
	
	for(auto [x, fr]: fr) {
		pq_weyes.push({fr, x});
	}
	
	for(auto cap: tables){
		pq_tables.push({1, cap});
	}
	
	
	lli ans = 0;
	while(!pq_weyes.empty()){
		auto [fr, wey] = pq_weyes.top(); pq_weyes.pop();
		
		auto [type, cap] = pq_tables.top(); pq_tables.pop();
		
		int matchs = min(fr, cap);
		if(type) ans += matchs;
		
		fr -= matchs;
		if(fr){
			pq_weyes.push({fr, wey});
		}
		
		cap -= matchs;
		if(cap) {
			pq_tables.push({0, cap});
		}
	}
	
	cout << ans << endl;
}


int main () {
	//fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

