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


int main () {
	//fastIO();

    int n; cin>>n;
    vector<int> nums(n);
    for(auto &x: nums) cin>>x;

    nums.push_back(0);
    sort(all(nums));


    // for(auto x: nums) cout << x << " ";
    // cout << endl;
    int max_diff = 0;
    n = SZ(nums);
    for(int i = 0; i < n-1; i++){
        max_diff = max(nums[i+1] - nums[i], max_diff);
    }

    int min_diff = 1e9 + 5;
    for(int i = 0; i < n-2; i++){
        min_diff = min(min_diff, nums[i+2] - nums[i]);
    }

    min_diff--;
    // debugg(max_diff);
    // debugg(min_diff);
    if(max_diff > min_diff) {
        cout << 0 << endl;
    } else {
        cout << min_diff << endl;
    }


	return 0;
}

