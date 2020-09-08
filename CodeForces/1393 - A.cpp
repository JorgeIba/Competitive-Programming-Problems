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
    lli n; cin>>n;
    if(n==1) cout << 1 << endl;
    else if(n==2) cout << 2 << endl;
    else cout << ((n/2) + 1) << endl;
}

int main()
{
    //fastIO();
    lli t; cin>>t;
    
    while(t--) solve();
    
    return 0;
}