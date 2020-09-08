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
    lli M, K; cin>>M>>K;
    lli q; cin>>q;
    while(q--)
    {
        lli cuanto; cin>>cuanto;
        lli aux = cuanto;
        lli minimo =  min(cuanto, 1000LL);
        lli total = M*minimo;
        cuanto -= minimo;
        total += cuanto*K;
        cout << aux << " " << total << endl;
    }
    return 0;
}