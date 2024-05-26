// Problem: A. Cut the Triangle
// Contest: Codeforces - Educational Codeforces Round 140 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1767/problem/0
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
	vector< pair<int,int> > points(3);
	
	for(int i = 0; i < 3; i++) cin>>points[i].first>>points[i].second;
	
	bool same_y = false, same_x = false;
	
	for(int i = 0; i < 3; i++){
		for(int j = i+1; j < 3; j++) {
			if(points[i].first == points[j].first) {
				same_x = true;
			}
			
			if(points[i].second == points[j].second) {
				same_y = true;
			}
			
		}
	}
	
	
	cout << (same_x && same_y ? "NO" : "YES") << endl;
	
	
}


int main () {
	//fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

