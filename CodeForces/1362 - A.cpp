#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;


void solve()
{
    lli a, b; cin>>a>>b;
    lli cA = 0, cB = 0;
    while(~a&1)
    {
        a>>=1;
        cA++;
    }
    while(~b&1)
    {
        b>>=1;
        cB++;
    }
    if(a != b)
    {
        cout<<-1<<endl;
        return;
    }
    lli diff = abs(cA - cB);
    lli mod8 = diff%3;
    lli mod4 = mod8%2;
    lli res = (lli)(diff/3) + (mod8/2) + (mod4);
    cout<< res <<endl;

}


int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--) solve();
    return 0;
}