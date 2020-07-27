#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;


void solve()
{
    lli n; cin>>n;
    lli res = 0, loga = log2(n);
    for(int i = 0; i<=loga; i++)
    {
        lli pawer = pow(2, i);
        lli aux = n/pawer;
        if(aux == 0)
        {
            break;
        }
        res += aux;
    }
    cout<<res<<endl;
}


int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}