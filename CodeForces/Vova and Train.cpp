#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

void solve()
{
    lli L, v, l, r; cin>>L>>v>>l>>r;
    lli total = L / v;
    lli Lower = (l-1) / v; 
    lli Upper = r / v;
    cout << total - (Upper-Lower)<<endl;
}


int main()
{
    //fastIO();
    lli t; cin>>t;
    while(t--) solve();
    
    return 0;
}