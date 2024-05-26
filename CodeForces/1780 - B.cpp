// Problem: B. GCD Partition
// Contest: Codeforces - Codeforces Round #846 (Div. 2)
// URL: https://codeforces.com/contest/1780/problem/B
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
	vector<lli> nums(n);
	lli sum = 0;
	for(auto &x: nums){
		cin>>x;
		sum += x;
	}
	
	lli sum_left = 0, sum_right = sum, ans = 1;
	for(int i = 0; i < n-1; i++) {
		auto num = nums[i];
		sum_left += num;
		sum_right -= num;
		ans = max(ans, __gcd(sum_left, sum_right));
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

