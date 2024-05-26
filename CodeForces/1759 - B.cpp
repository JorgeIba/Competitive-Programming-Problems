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


void solve(){
	lli n, k; cin>>n>>k;
	
	set<lli> numbers;
	for(int i = 1; i <= 500; i++) numbers.insert(i);
	
	vector<lli> nums(n);
	for(int i = 0; i < n; i++) {
		lli num; cin>>num;
		numbers.erase(num);
		nums[i] = num;
	}
	
	
	lli maxi = *max_element(all(nums));
	
	
// 	cout << maxi << endl;
//	for(auto x: numbers) cout << x << " ";
	
	lli sum = 0;
	for(auto x: numbers) {
		if(x > maxi) {
			if(sum == k) {
				cout << "YES\n";
				return;
			}
			else if(sum > k) {
				cout << "NO\n";
				return;
			}
		}	
		sum += x;
	}
	
	cout << "NO\n";
}



int main () {
	//fastIO();
	
	lli t; cin>>t;
	
	while(t--) solve();

	return 0;
}
