#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli INF = 1e18;

vector<lli> ST;
lli n, k;

char contrario(char c)
{
    if(c=='1') return '0';
    return '1';
}

//11
lli query(lli l, lli r) //Node could be just an integer
{
    lli MAX1 = INF;
    lli MAX2 = INF;
    for(l+=n, r+=n; l<=r; l>>=1, r>>=1)
    {
        if(l&1) MAX1 = min(MAX1, ST[l++]);   
        if(~r&1) MAX2 = min(ST[r--],MAX2);
    }
    return min(MAX1, MAX2);
}
//10
lli update(int index, lli value)
{
    index+=n;
    ST[index] = min(value, ST[index]);
    for(; index; index>>=1)
    {
        ST[index>>1] = min(ST[index], ST[index^1]);
    }
}


map<lli,lli> notAlternating;

void build()
{
    isAlternating;
    for(int i = 0; i<n; i++)
    {

    }
}


void solve()
{
    cin>>n>>k;
    string s; cin>>s;
    ST.clear(); ST.resize(2*n);
    build(s);
    
    vector<lli> dp(n+1, INF);
    dp[n-1] = 0;
    for(int i = n-1; i>=0; i--)
    {
        lli j = i;
        bool alternando = true;
        dp[i] = min(dp[i], 1 +  ( (j+1<n) ? query(j+1, j+1+k): -1 ) );
        update(i, dp[i]);
        //dp[i] = query(i, min(, ) ) + 1;
    }
    cout<<dp[0];

}


int main()
{
    //fastIO();
    lli t; cin>>t;
    while(t--)
    {
        solve();
        if(t!=0)
        {
            cout<<endl;
        }
    } 

    return 0;
}