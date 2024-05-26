#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

const int maxN = 18;
int mat[maxN+1][maxN+1];
vector<int> nums;


int n, m, k; 
lli dp[maxN+1][(1 << maxN)];
const lli INF = 1e18;

lli f(int last, int mask){
    if(__builtin_popcount(mask) == m) return 0;


    lli &ans = dp[last][mask];
    if(ans != -1) return ans;

    ans = 0;

    for(int i = 0; i < n; i++){
        if(~mask & (1 << i)) {
            ans = max(ans, f(i, mask ^ (1 << i)) + nums[i] + mat[last][i]);
        }
    }
    return ans;
}



int main () {
	//fastIO();
    cin>>n>>m>>k;
    nums.resize(n);

    for(auto &x: nums) cin>>x;

    for(int i = 0; i < k; i++){
        int u, v, c; cin>>u>>v>>c; u--, v--;
        mat[u][v] = c;
    }

    memset(dp, -1, sizeof(dp));

    lli ans = 0;
    for(int i = 0; i < n; i++) {
        ans = max(ans, f(i, (1 << i)) + nums[i]);
    }
    cout << ans << endl;



	return 0;
}

