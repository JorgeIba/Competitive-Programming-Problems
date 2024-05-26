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

const int MOD = 1e9+7;
const int inv2 = (MOD+1)/2;
const int MAXN = 500 + 50;

int dp[MAXN][MAXN];

int main () {
	//fastIO();

    int n, m; cin>>n>>m;
    vector<int> blocks(n);
    for(auto &x: blocks) cin>>x;
    blocks.push_back(m+1);

    memset(dp, -1, sizeof(dp));
    auto f = [&](const auto &f, int i, int j) -> int {
        if(i == j) return 0;

        int &ans = dp[i][j];
        if(ans != -1) return ans;

        ans = 0;
        if(j == m+1){
            return ans = (1 + f(f, i+1, j)) % MOD;
        }

        int yes = 1LL * inv2 * (1 + f(f, i+1, j)) % MOD;
        int no = 1LL * inv2 * f(f, i, j+1) % MOD;
        ans = (yes + no) % MOD;
        return ans;
    };

    int ans = 0;
    forn(i, n){
        ans += f(f, blocks[i], blocks[i+1]);
        if(ans >= MOD) ans -= MOD;
    }

    cout << ans << endl;



	return 0;
}

