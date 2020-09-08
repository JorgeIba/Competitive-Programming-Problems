#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;


const lli MOD = 986424689;

lli binPow(lli a, lli b)
{
    lli res = 1;
    a = a%MOD;
    while(b)
    {
        if(b&1) res = (res*a)%MOD;
        b>>=1;
        a = (a*a)%MOD;
    }
    return res%MOD;
}


void solve()
{
    lli a, n; cin>>a>>n;

    if(a==1)
    {
        lli inverse = binPow(2, MOD-2);
        lli res = ((((n%MOD) * ((n%MOD) + 1))%MOD) * inverse)%MOD;
        cout<< res << endl;
        return;
    }

    lli inverse = binPow( binPow(a-1,2), MOD-2  );

    lli parte2 = ( (((a*(n%MOD))%MOD) - (n%MOD) - (1%MOD))%MOD );
    if(parte2 < 0) parte2+=MOD;

    lli res = ((( ((binPow(a, n+1)  * parte2)%MOD) + a)%MOD) * inverse)%MOD;

    

    cout << res << endl;

}



int main()
{
    //fastIO();
    lli t; cin>>t;
    while(t--) solve();
    return 0;
}