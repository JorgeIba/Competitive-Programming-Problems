#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli MOD = 1000000007;

int main()
{
    fastIO();
    lli n; cin>>n;
    vector< lli > fibo(n+1);
    fibo[0] = fibo[1] = 1;
    for(int i = 2; i<=n; i++)
    {
        fibo[i] = (fibo[i-1] + fibo[i-2])%MOD;
    }
    
    vector<lli> ans(n+1);
    ans[1] = 1;
    for(int i = 2; i<=n; i++)
    {
        ans[i] = (ans[i-1] + fibo[i])%MOD;
    }
    cout << ans[n] << endl;
    
    return 0;
}