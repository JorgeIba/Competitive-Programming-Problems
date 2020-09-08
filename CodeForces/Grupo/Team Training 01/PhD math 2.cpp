#include <bits/stdc++.h>
 
#define lli unsigned long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
 
using namespace std;
 
 
void solve()
{
    lli t, a, b, n, p;  cin>>a>>b>>n>>p;
    vector<lli> s;
    lli aux = a, x = n;
    lli index = 0;
    while(x--)
    {
        aux*=10;
        lli fl = aux/b;
        s.push_back(fl);
        aux -= b*fl;
    }
    t = s.size();
    //vector< vector<lli> > dp(p, vector<lli>(t, 0));
    vector< vector<lli> > dp(p, vector<lli>(2, 0));
    lli ans = 0;

    dp[ s[0]%p ][0] += 1;
    ans += dp[0][0];
    for(int i = 1; i<t; i++) //dp[i][1] -> en le indice actual, todas las veces que aparece i | 1 actual | 0 pasado
    {
        for(int j = 0; j<p; j++)
        {
            lli res = (j * 10 + s[i])%p;
            dp[res][1] += dp[j][0];
        }
        dp[ s[i]%p ][1] += 1;
        ans += dp[0][1];
        for(int j = 0; j<p; j++)
        {
            dp[j][0] = dp[j][1];
            dp[j][1] = 0;
        }
    }  
    cout<<ans<<endl;
}
 

int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--) solve();
    return 0;
}