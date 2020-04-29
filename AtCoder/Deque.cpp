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

vector< vector< vector<lli> > > dp(    3010, vector<vector<lli>> (  3010, vector<lli>(2, -1)  )    );
lli dp[3010][3010][2];


lli f(lli l, lli r, lli estado) //estado 0-> max, 1-> min
{
    //debug2(l,r);
    lli size = r - l + 1;
    if(size<=0) return 0;
    if(dp[l][r][estado] != -1) return dp[l][r][estado];
    if(estado == 0)
    {
        lli uno = f(l+1, r, !estado) + cola[l] ;
        lli dos = f(l, r-1, !estado) + cola[r];
        return dp[l][r][estado] = max(uno,dos);
    }
    else
    {
        lli uno = f(l+1, r, !estado) - cola[l];
        lli dos = f(l, r-1, !estado) - cola[r];
        return dp[l][r][estado] = min(uno,dos);
    }
    
}





int main()
{
    fastIO();
    //memset(dp, -1, sizeof(dp));
    cin>>n;
    cola.resize(n);
    for(auto &x: cola)
    {
        cin>>x;
    }
    cout<<f(0,n-1,0)<<endl;

    return 0;
}