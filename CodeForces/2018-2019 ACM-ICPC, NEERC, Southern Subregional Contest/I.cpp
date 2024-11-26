#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef long long int lli;
typedef long double ld;


int main () {
	// fastIO();

    int n; cin>>n;
    vector<int> nums(n);
    for(auto &x: nums) cin>>x;

    sort(all(nums));
    int ans = 0;
    for(int i = 1; i < n; i++) {
        ans += ((nums[i]-1) - (nums[i-1]+1) + 1);
    }
    cout << ans << endl;


	return 0;
}

