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

void main_() {
    int n; cin>>n;
    vector<lli> nums(n);
    for(auto &x: nums)
        cin>>x;

    lli ans = 1;
    for(int i = 0; i+1 < n; i += 2) {
        ans = max(ans, nums[i+1] - nums[i]);
    }

    if(n % 2 == 0) {
        cout << ans << endl;
        return;
    }

    ans = 1e18 + 5;
    for(int i = 0; i < n; i++) {
        vector<lli> new_v;
        for(int j = 0; j < n; j++) {
            if(j == i) continue;
            new_v.push_back(nums[j]);
        }

        lli ans_2 = 1;
        for(int j = 0; j+1 < SZ(new_v); j += 2) {
            ans_2 = max(ans_2, new_v[j+1] - new_v[j]);
        }

        ans = min(ans, ans_2);
    }

    cout << ans << endl;

}

int main () {
	fastIO();

	int t = 1;
	cin>>t;

	while(t--) {
		main_();
	}

	return 0;
}

