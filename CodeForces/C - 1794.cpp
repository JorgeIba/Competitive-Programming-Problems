// Problem: C. Scoring Subsequences
// Contest: Codeforces - Codeforces Round 856 (Div. 2)
// URL: https://codeforces.com/contest/1794/problem/C
// Memory Limit: 256 MB
// Time Limit: 2500 ms
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
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;


void solve(){
	int n; cin>>n;
	vector<int> nums(n);
	
	for(auto &x: nums) cin>>x;

	deque<int> num_active;
	int taken_off = 0;
	
	vector<int> ans(n);
	for(int i = 0; i < n; i++) {
		auto num = nums[i];
		num_active.push_back(num);
		int start = (i+1) - (taken_off);

		// cout << "ACTIVES:" << endl;
		// for(auto x: num_active) cout << x << " ";
		// cout << endl;

		// debugg(taken_off);
		// debugg(start);

		int curr = start;
		while(num_active.front() < curr) {
			taken_off++;
			num_active.pop_front();
			curr--;
		}
		
		ans[i] = (i+1) - taken_off;
	}
	
	for(auto x: ans) cout << x << " ";
	cout << endl;
	
}


int main () {
	//fastIO();
	
	int t; cin>>t;
	while(t--) solve();


	return 0;
}

