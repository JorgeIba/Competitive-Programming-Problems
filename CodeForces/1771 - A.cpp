// Problem: A. Hossam and Combinatorics
// Contest: Codeforces - Codeforces Round #837 (Div. 2)
// URL: https://codeforces.com/contest/1771/problem/0
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
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

void main_(){
	int n; cin>>n;
	vector<lli> nums(n);
	for(auto &x: nums) cin>>x;
	
	lli mx = *max_element(all(nums));
	lli mn = *min_element(all(nums));
	
	lli mx_c = count(all(nums), mx);
	lli mn_c = count(all(nums), mn);
	
	lli ans = 2 * mx_c * mn_c;
	
	if(mx == mn) ans = mx_c*(mn_c-1);
	else ans = 2 * mx_c * mn_c;
	
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

