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
    lli R, r, k; cin>>R>>r>>k;
    ld OX = 2.0*R, OY = 2.0*r;
    ld OXp = (ld) R / 2.0, OYp = (ld) (R*R) / (2.0*r);
    ld D = (double)(R*(R-r)) / (2*r), RF = D / 2;
    ld OAB = sqrt( (double)  (OXp + RF)*(OXp + RF)   +   (2*RF*k)*(2*RF*k) );
    ld OBp = OAB - RF, OAp = OAB + RF;
    ld OB = R*R / OBp, OA = R*R / OAp;

    //cerr << RF << " " << OAB << " " << OAB << " " << OBp << " " << OAp << " " << OB << " " << OA << endl;

    cout << fixed << setprecision(10);

    cout << (OB - OA) / 2 << endl;

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