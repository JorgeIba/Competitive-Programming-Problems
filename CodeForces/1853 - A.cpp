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

	int ans = 2e9 + 100;
	for(int i = 0; i < n-1; i++){
		if(nums[i+1] < nums[i]) ans = 0;
		ans = min(ans, (nums[i+1] - nums[i])/2 + 1);
	}
	ans = max(ans, 0);

	cout << ans << endl;
}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

