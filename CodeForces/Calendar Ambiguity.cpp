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
    lli months, monthlen, weeklen; cin>>months>>monthlen>>weeklen;
    lli l = min(months, monthlen);
    lli modulo = weeklen / (__gcd(weeklen, monthlen-1));
    // x = y (mod modulo)
    lli cabe = l / modulo;
    lli ans = ((cabe*(cabe-1))/2) * modulo;
    lli resto = l % modulo;
    ans += (resto*(cabe));

    cout << ans << endl;
}


int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--) solve();

    return 0;
};