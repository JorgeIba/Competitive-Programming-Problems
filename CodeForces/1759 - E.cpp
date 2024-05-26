// Problem: E. The Humanoid
// Contest: Codeforces - Codeforces Round  #834 (Div. 3)
// URL: https://codeforces.com/contest/1759/problem/E
// Memory Limit: 256 MB
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

typedef vector<lli> VLL;
typedef vector<int> VI;


lli f(lli h, const vector<lli> &nums, vector<lli> options) {
	lli ans = 0;
	lli n = SZ(nums);
	
	
	for(int i = 0; i < n; i++) {
		auto a_i = nums[i];
// 		cout << h << " " << a_i << " " << SZ(options) << endl;
		if(a_i < h) {
			h += (a_i/2);
			ans++;
		} else {
			while(!options.empty()) {
				auto op = options.back();
				options.pop_back();
				
				h = h*op;
				if(a_i < h) {
					i--;
					break;
				}
			}
		}
	}
	return ans;
}




void solve() {
	lli n, h; cin>>n>>h;
	vector<lli> nums(n);
	for(auto &x: nums) cin>>x;
	
	sort(all(nums));
	

	lli ans = 0;
	
	vector<lli> options = {2, 2, 3};
	
	do{
		lli ans_i = f(h, nums, options);
		ans = max(ans, ans_i);		
	}while(next_permutation(all(options)));

	cout << ans << endl;
	
}




int main () {
	//fastIO();
	
	int t; cin>>t;
	
	while(t--) solve();
	
	return 0;
}