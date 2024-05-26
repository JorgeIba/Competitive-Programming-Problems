// Problem: C. Another Array Problem
// Contest: Codeforces - Codeforces Round #840 (Div. 2) and Enigma 2022 - Cybros LNMIIT
// URL: https://codeforces.com/contest/1763/problem/C
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
		
	lli mn = *min_element(all(nums));
	lli mx = *max_element(all(nums));
	
	if(n == 1){
		cout << nums[0] << endl;
	} else if(n == 2){
		cout << max(nums[0] + nums[1], 2 * (mx - mn)) << endl;
	} else if(n == 3) {

		lli sum_1 = nums[0] + nums[1] + nums[2];
		lli sum_2 = nums[0] * 3;
		lli sum_3 = nums[2] * 3;
		lli sum_4 = nums[0] + 2*(abs(nums[1] - nums[2]));
		lli sum_5 = nums[2] + 2*(abs(nums[1] - nums[0]));
		
		lli diff_1 = abs(nums[1] - nums[2]); 
		lli sum_6 = diff_1 + 2*abs(diff_1 - nums[0]);
		
		lli diff_2 = abs(nums[0] - nums[1]); 
		lli sum_7 = diff_1 + 2*abs(diff_2 - nums[2]);
		
		lli sum_8 = 3 * abs(nums[0] - nums[1]);
		lli sum_9 = 3 * abs(nums[1] - nums[2]);
			
		cout << max({sum_1, sum_2, sum_3, sum_4, sum_5, sum_6, sum_7, sum_8, sum_9}) << endl;
	}
	if(n >= 4){
		cout << n * (mx) << endl;
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

