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
    lli h, c, t; cin>>h>>c>>t;
    lli x, x0;
    
    if( 0<= h + c - 2*t)
    {
        cout<<2<<endl;
        return;
    }
    x = ( (c-t) / (h+c-2*t) );
    x0 = x + 1;

    lli completeX = abs (x*h + (x-1)*c - (2*x-1)*t);
    lli completeX0 = abs(x0*h + (x0-1)*c - (2*x0-1)*t);
    //cout<<completeX<<" "<<completeX0<<endl;
    if(completeX*(2*x0-1) <= completeX0*(2*x-1))
    {
        cout<< (2*x - 1 ) << endl;
    }
    else
    {
        cout<< (2*x0 - 1) << endl;
    }
    

    
    

}


int main()
{
    //fastIO();
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}