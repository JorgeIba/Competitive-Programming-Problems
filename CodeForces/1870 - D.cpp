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

    int k; cin>>k;

    int lower = 0;
    for(int i = 0; i < n; i++){
        if(nums[i] <= nums[lower])
            lower = i;
    }

    vector<int> suffix(n);

    auto get_ans = [&](){
        vector<int> ans(n);
        for(int i = n-1; i >= 0; i--){
            if(i+1 < n) ans[i] = ans[i+1];
            ans[i] += suffix[i];
        }
        for(auto x: ans) cout << x << " ";
        cout << endl;
    };

    suffix[lower] = k / nums[lower];

    auto get_possible = [&](int rem, int low, int k, int trying){
        if(trying == low) return k;
        return min(k, rem / (trying - low) );
    };

    for(int i = n-2; i >= 0; i--){
        nums[i] = min(nums[i+1], nums[i]);
    }

    int rem = k % nums[lower];
    int last = lower;
    for(int r = lower+1; r < n; r++){
        int k = get_possible(rem, nums[last], suffix[last], nums[r]);
        suffix[r] = k;
        rem = rem + 1LL * k * (nums[last] - nums[r]);
        suffix[last] -= k;
        last = r;
    }

    get_ans();
}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

