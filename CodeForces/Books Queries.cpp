#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli INF = 1e18;
int main()
{
    fastIO();
    lli q; cin>>q;
    lli maxN = 200010;
    map<lli,lli> poss;
    lli posL = -1, posR = 1; // el primero que llegue lo fijas como punto de referencia
    lli primero = 0;
    for(int YAENTRAALVPORFAVOR = 0; YAENTRAALVPORFAVOR<q; YAENTRAALVPORFAVOR++)
    {
        char t; cin>>t;
        lli id; cin>>id;
        if(YAENTRAALVPORFAVOR == 0) continue;

        if(t == 'L')
        {
            assert(id < maxN);
            poss[id] = posL--;;
        }
        else if(t == 'R')
        {
            assert(id < maxN);
            poss[id] = posR++;
        }
        else
        {
            cout << min( (poss[id]-posL), abs(poss[id]-posR) ) - 1 << endl;
        }
    }

    
    return 0;
}