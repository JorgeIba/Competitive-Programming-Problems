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


void solve() {
	lli n; cin>>n;
	vector<lli> nums(n);
	for(auto &x: nums) cin>>x;
	

	lli ans = 0, prefix_sum = 0;
	for(int i = 0; i < n; i++) {
		lli num = nums[i];
		if(num == 0) {
			
			map<lli,lli> fr;
			fr[prefix_sum]++;

			lli j = i+1;
			while(j < n && nums[j]) {
				prefix_sum += nums[j];
				fr[prefix_sum]++;
				j++;
			}

			lli maxi = 0, val = -1;
			for(auto [num, frq]: fr) {
				if(maxi < frq) {
					maxi = frq;
					val = num;
				}
			}

			ans += maxi;
			num = -val;
			i = j-1;
		} else {
			ans += (prefix_sum == -num);
		}

		prefix_sum += num;
	}
	
	cout << ans << endl;
}

int main () {
	fastIO();
	
	int t; cin>>t;
	while(t--) solve();

	return 0;
}

