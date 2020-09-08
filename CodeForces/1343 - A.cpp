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
    lli t; cin>>t;
    while(t--)
    {
        lli n; cin>>n; // x * (2^k - 1) = n
        for(int i = 2; i<=30; i++)
        {
            if( n % ( (1<<i) - 1) == 0)
            {
                cout << n/((1<<i) - 1) << endl;
                break;
            }
        }
    }

    return 0;
}