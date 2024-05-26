#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

vector<lli> nums;

const lli MOD = 1e9+7;
const lli maxN = 1e6+10;
lli dp[maxN][5];

lli f(int idx, int looking){
    if(idx == SZ(nums)) return looking == 4;

    auto num = nums[idx];

    lli &ans = dp[idx][looking];
    if(ans != -1) return ans;

    if(num == looking) {
        if(looking == 2){
            return ans = (f(idx+1, looking) + f(idx+1, looking) + f(idx+1, looking + 1)) % MOD;
        } else {
            return ans = (f(idx+1, looking) + f(idx+1, looking+1)) % MOD;
        }
        
    } else {
        return ans = f(idx+1, looking);
    }
}


int main () {
	//fastIO();
	
    int n; cin>>n;
    nums.resize(n);

    for(auto &x: nums) cin>>x;

    memset(dp, -1, sizeof(dp));
    cout << f(0, 1) << endl;

	return 0;
}

