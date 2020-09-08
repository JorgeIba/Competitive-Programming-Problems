#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;
const lli INF = 1e18;

void solve()
{
    lli T, n; cin>>T>>n;
    vector< lli > songs(n);
    for(auto &x: songs) cin>>x;
    lli cont = 1, total = 0;
    for(int i = songs[0]+1; true; i++)
    {
        if(cont == n) break;
        lli distAdelante = INF;
        lli distAtras = INF;
        if(i > songs[cont]) 
        {
            distAdelante = (T - i) + songs[cont];
            distAtras = (i - songs[cont]);
            //cerr << distAdelante << " A " << distAtras << endl;
        }
        else
        {
            distAdelante = songs[cont] - i;
            distAtras = i + (T-songs[cont]);
            //cerr << distAdelante << " B " << distAtras << endl;
        }
        total += min(distAdelante, distAtras);
        i = songs[cont];
        cont++;
    }
    cout << total << endl;
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