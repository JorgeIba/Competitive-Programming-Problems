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
    //fastIO();
    lli la, ra, ta; cin>>la>>ra>>ta;
    lli lb, rb, tb; cin>>lb>>rb>>tb;

    lli modulo = (ta*tb) / __gcd(ta, tb);

    if(la > lb)
    {
        swap(la, lb);
        swap(ra, rb);
        swap(ta, tb);
    }

    if(ta == tb)
    {
        cout << ( min(ra, rb) - max(la, lb) + 1 ) << endl;
    }
    else
    {
        lli d = __gcd(ta, tb);
        if((lb-la)%d == 0)
        {
            cout << min(  ra - la + 1, rb - lb + 1  ) << endl;
        }
        else
        {
            lli candidato1 = ceil((double)(la-lb)/d);
            lli candidato2 = floor((double)(la-lb)/d);
            lli la1 = la + candidato1*ta;
            lli lb1 = lb + candidato1*tb;
            lli ra1 = ra + candidato1*ta;
            lli rb1 = rb + candidato1*tb;

            lli ans1 = ( ( min(ra1, rb1) - max(la1, lb1) +1 )   );

            lli la2 = la + candidato2*ta;
            lli lb2 = lb + candidato2*tb;
            lli ra2 = ra + candidato2*ta;
            lli rb2 = rb + candidato2*tb;


            lli ans2 = ( ( min(ra2, rb2) - max(la2, lb2) +1 )   );
            cerr << ans1 << " " << ans2 << endl;
            cout << max(ans1, ans2) << endl;
        }
        
        
    }
    
    

    return 0;
}