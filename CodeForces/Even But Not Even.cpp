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
    string s; cin>>s;
    string res;
    for(auto c: s)
    {
        if(  (int)(c-'0') % 2 == 1 && res.length()<=1) res+=c;
    }
    if(res.length() >= 2) cout << res << endl;
    else cout << -1 << endl;
}


int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--) solve();

    return 0;
}