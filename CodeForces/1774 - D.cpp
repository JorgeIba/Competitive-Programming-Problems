// Problem: D. Same Count One
// Contest: Codeforces - Polynomial Round 2022 (Div. 1 + Div. 2, Rated, Prizes!)
// URL: https://codeforces.com/contest/1774/problem/D
// Memory Limit: 512 MB
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

void main_(){
	int n, m; cin>>n>>m;
	vector< vector<int> > mat(n, vector<int>(m));
	for(auto &v: mat){
		for(auto &x: v) cin>>x;
	}
	
	lli total = 0;
	for(auto v: mat){
		for(auto x: v) {
			total += (x == 1);
		}
	}
	

	if(total == 0){
		cout << 0 << endl;
		return;
	}
	
	if(total % n != 0) {
		cout << -1 << endl;
		return;
	}
	
	lli equals = total / n;
	
	vector<int> how_many(n);
	for(int i = 0; i < n; i++){
		lli have = count(all(mat[i]), 1);
		how_many[i] = have - equals;
	}
	
	vector< tuple<lli,lli,lli> > ans;
	for(int col = 0; col < m; col++){
		vector<lli> idx_exceeds, idx_needs;
		for(int row = 0; row < n; row++) {
			if(how_many[row] > 0 && mat[row][col] == 1) idx_exceeds.push_back(row);
			else if(how_many[row] < 0 && mat[row][col] == 0) idx_needs.push_back(row);
		}
		
		while(SZ(idx_exceeds) && SZ(idx_needs)){
			auto exc = idx_exceeds.back(), need = idx_needs.back();
			ans.push_back({exc+1, need+1, col+1});
			idx_exceeds.pop_back();
			idx_needs.pop_back();
			how_many[exc]--;
			how_many[need]++;
		}
	}
	
	cout << SZ(ans) << endl;
	for(auto [x, y, c]: ans){
		cout << x << " " << y << " " << c << endl;
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

