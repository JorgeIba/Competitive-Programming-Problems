#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

vector< vector< lli > > f;
vector< lli > nums;

int main () {
	fastIO();
    lli n; cin>>n;
    nums.resize(n+1);

    for(int i = 1; i<=n; i++) cin>>nums[i];

    f.assign(n+1, vector<lli>(n+1));
    f[1][1] = nums[1];
    for(int i = 2; i<=n; i++)
    {
        f[i][1] = nums[i];
        for(int j = 2; j<=i; j++)
        {
            f[i][j] = f[i-1][j-1] ^ f[i][j-1];
        }
    }

    vector< vector< lli > > dp(n+2, vector<lli>(n+2, 0));
    dp[n][n] = nums[n];
    for(int L = n; L>=1; L--)
    {
        for(int R = L; R<=n; R++)
        {
            lli diff = R - L + 1;
            dp[L][R] = max( {f[R][diff], dp[L][R-1], dp[L+1][R]} );
        }
    }

    lli q; cin>>q;
    while(q--)
    {
        lli l, r; cin>>l>>r;
        cout << dp[l][r] << endl;
    }
	return 0;
}