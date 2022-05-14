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
 

void solve()
{
    lli n, m; cin>>n>>m;
    vector<bitset<500>> covers(m);
    bitset<500> check;
    for(int i = 0; i<m; i++)
    {
        string s; cin>>s;
        for(int j = 0; j<n; j++)
        {
            if(s[j] == '0') covers[i][j] = 0;
            else covers[i][j] = 1;
        }
        check |= covers[i];
    }

    if(check.count() < n)
    {
        cout << -1 << endl;
        return;
    }

    lli dp[(1<<m)]; //dp[mask] con las mask cuantos cubro?
    dp[0] = 0;
    for(int mask = 0; mask<(1<<m); mask++)
    {
        bitset<500> ans;
        for(int i = 0; i<m; i++)
        {
            if(mask & (1<<i))
            {
                ans |= covers[i];
            }
        }
        dp[mask] = ans.count();
    }

    lli ans = 1e18;

    for(int mask = 0; mask<(1<<m); mask++)
    {
        if(dp[mask] == n)
        {
            bitset<500> aux = mask;
            ans = min(ans, (lli)aux.count());
        }
    }
    cout << ans << endl;
}

 
int main () {
	fastIO(); 
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
	return 0;
}