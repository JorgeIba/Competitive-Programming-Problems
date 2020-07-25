#include <bits/stdc++.h>
#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;



int main()
{
    fastIO();
    lli n, m; cin>>n>>m;
    set< tuple<lli,lli,lli> > check;
    lli start = 1;
    for(int i = 0; i<n; i++)
    {
        lli ci, ti; cin>>ci>>ti;
        lli duracion = ci*ti;
        check.insert({start, start+duracion-1, i+1});
        start = start+duracion;
    }

    const lli INF = 1e18;
    for(int i = 0; i<m; i++)
    {
        lli t; cin>>t;
        auto itr = check.upper_bound({t,INF,INF});
        itr--;
        cout << get<2>((*itr)) << endl;
    }
    

    return 0;
}