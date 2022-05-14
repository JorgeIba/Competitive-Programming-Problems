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


lli check(lli t, vector<lli> &nums) {
    lli left = 0, right = 0;
	for(auto x: nums) {
        if(x == t) continue;
        else if(x < t) left += x;
        else right += x;
    }

    // cout << left << " " << right << endl;

    if(left == right) return 1;
    else if(left > right) return 2;
    else return 3;

}


int main () {
	//fastIO();

	lli n; cin>>n;

	vector<lli> nums(n);
	for(auto &x: nums) cin>>x;

	lli l = 1, r = 2e5+1, ans = -1;

	while(l <= r) {
		lli mid = l + (r-l) / 2;
        lli flag = check(mid, nums);
        // cout << mid << " " << flag << endl;
		if( flag == 1 ) { // todo bien
			ans = mid;
			r = mid-1;
		} else if(flag == 2) {
            r = mid-1;
        } else {
			l = mid+1;
		}
	}
	cout << ans << endl;


	return 0;
}

