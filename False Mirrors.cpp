#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<lli> monsters;
const lli INF = 1e18, maxN = 21;
lli n; 
lli dp[1<<maxN];

lli fun(lli mask)
{
    if( mask == 0) return 0;
    lli &res = dp[mask];
    if(res != -1) return dp[mask];
    res = INF;
    for(int i = 0; i<n; i++)
    {
        if( !(mask&(1<<i)) ) continue;
        lli aux = 0;
        if(i == 0)
            aux =  (1<<(n-1)) | (1<<1) | (1<<0)  ;
        
        else if(i == n-1)
            aux =  (1<<(n-2)) | (1<<(n-1)) | (1<<0);
        
        else
            aux = (1<<(i-1)) | (1<<i) | (1<<(i+1));

        lli newMask = mask&( ~aux );
        lli putazos = 0;
        for(int i = 0; i<n; i++)
        {
            if(newMask&(1<<i))
            {
                putazos += monsters[i];
            }
        }
        res = min(res, fun(newMask) + putazos);
    }
    return res;
}



int main()
{
    fastIO();
    memset(dp, -1, sizeof(dp));
    cin>>n;
    monsters.resize(n);
    for(int i = 0; i<n; i++)
    {
        cin>>monsters[i];
    }
    cout<<fun( (1<<n) - 1  )<<endl;

    return 0;
}