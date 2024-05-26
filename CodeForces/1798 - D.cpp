// Problem: D. Shocking Arrangement
// Contest: Codeforces - Codeforces Round 860 (Div. 2)
// URL: https://codeforces.com/contest/1798/problem/D
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
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;


void main_(){
	int n; cin>>n;
	
	vector<int> nums(n);
	for(auto &x: nums) cin>>x;
	
	int maxi = *max_element(all(nums));
	int mini = *min_element(all(nums));

	vector<int> negs, pos;
	forn(i, n) {
		if(nums[i] < 0) {
			negs.push_back(nums[i]);
		} else {
			pos.push_back(nums[i]);
		}
	}

	sort(all(negs));
	sort(all(pos));
		
	reverse(all(negs));
	reverse(all(pos));
		
		
	lli limit = maxi - (mini);
	vector<int> ans;
	
		
	auto push_neg = [&](){
		ans.push_back( negs.back() );
		negs.pop_back();
	};

	auto push_pos = [&](){
		ans.push_back( pos.back() );
		pos.pop_back();		
	};
		

	lli sum = 0;
	for(int i = 0; i < n; i++){
		
		if(pos.empty()) {
			push_neg();
		} else if(negs.empty()) {
			push_pos();
		} else {
			if(sum > 0) {
				push_neg();
			} else if(sum < 0){
				push_pos();	
			} else {
				if(negs.back() < pos.back()){
					push_neg();
				} else {
					push_pos();
				}
			}
		}
		
		
		sum += ans.back();
		
		if(abs(sum) >= limit) {
			cout << "No" << endl;
			return;
		}
	}
	
	cout << "Yes" << endl;
	for(auto x: ans) cout << x << " ";
	cout << endl;
	
}


int main () {
	//fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

