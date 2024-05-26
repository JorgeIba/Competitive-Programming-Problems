// Problem: B. Block Towers
// Contest: Codeforces - Educational Codeforces Round 140 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1767/problem/B
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

using namespace std;

void main_(){
	int n; cin>>n;
	vector<lli> nums(n);
	for(auto &x: nums) cin>>x;
	
	vector<lli> nums_x(nums.begin() + 1, nums.end());
	
	sort(all(nums_x));
	
//	for(auto x: nums_x) cout << x << " ";
	//cout << endl;
	
	lli start_n = nums[0];
	for(int i = 0; i < SZ(nums_x); i++) {
		auto num = nums_x[i];
		if(num <= start_n) continue;
		start_n = ((num+start_n)/2 + (num+start_n)%2);
	}
	
	cout << start_n << endl;
	
}


int main () {
	//fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

