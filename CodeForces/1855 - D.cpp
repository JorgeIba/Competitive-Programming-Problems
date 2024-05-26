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

const int MAXN = 2e5 + 100;

int main () {
	fastIO();

    int n; cin>>n;

    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;
    
    bitset<MAXN> dp;
    dp[0] = 1;

    for(int i = 0; i < n; i++){
        auto x = nums[i];
        dp |= ( (dp>>i) << (x+i) );
    }
    
    lli ans = 0;
    lli sum = 0;
    for(int i = 0; i < 2*MAXN; i++){
        if(i < n) sum += nums[i];

        if(dp[i]){
            ans = max(ans, sum - i);
        }
    }
    cout << ans << endl;


	return 0;
}