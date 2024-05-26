// Problem: C. Doremy's City Construction
// Contest: Codeforces - Codeforces Global Round 24
// URL: https://codeforces.com/contest/1764/problem/C
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
	int n; cin>>n;
	vector<lli> nums(n);
	
	for(auto &x: nums) cin>>x;
	
	map<lli,lli> fr;
	for(auto x: nums) fr[x]++;
	
	if(SZ(fr) == 1){
		cout << n / 2 << endl;
		return;
	}
	
	
	sort(all(nums));
	
	lli cut = nums[  (n-1)/2  ];
	
	lli lower = 0, greater = 0;
	for(auto [x, fr_x]: fr){
		if(x <= cut) lower += fr_x;
		else greater += fr_x;
	}

	lli ans_1 = lower*greater;

	lower = 0, greater = 0;
	for(auto [x, fr_x]: fr){
		if(x < cut) lower += fr_x;
		else greater += fr_x;
	}
	lli ans_2 = lower*greater;

	
	cout << max(ans_1, ans_2) << endl;
	
}


int main () {
	//fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

