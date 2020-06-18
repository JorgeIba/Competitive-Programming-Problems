#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli INF = 1e18;

char contrario(char c)
{
    if(c=='1') return '0';
    return '1';
}


void solve()
{
    lli n, k; cin>>n>>k;
    string s; cin>>s;
    
    
    vector<lli> dp(n+1, INF);
    for(int i = n-1; i>=0; i--)
    {
        bool alternando = true;
        for(int j = i; j-i+1 <= k && j<n; j++)
        {
            if(contrario(s[j-1]) != s[j]  &&  (j-i+1)>1 ) alternando = false;
            if(!alternando || (j-i+1) == 1) 
            {
                dp[i] = min(dp[i], 1 +  ( (j+1<n) ? dp[j+1]: -1 ) );
            }
        }
    }
    cout<<dp[0];

}


int main()
{
    fastIO();
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