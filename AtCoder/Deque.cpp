#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

lli n;
vector<lli> cola;
lli dp[3010][3010];


lli f(lli l, lli r)
{
    //debug2(l,r);
    if(l>r) return 0;

    if(dp[l][r] != -1) return dp[l][r];

    lli uno = cola[l] - f(l+1, r) ;
    lli dos = cola[r] - f(l, r-1) ;
    //return max(uno, dos);
    return dp[l][r] = max(uno,dos);
    
}

int main()
{
    fastIO();
    memset(dp, -1, sizeof(dp));
    cin>>n;
    cola.resize(n);
    for(auto &x: cola)
    {
        cin>>x;
    }
    cout<<f(0,n-1)<<endl;

    return 0;
}
