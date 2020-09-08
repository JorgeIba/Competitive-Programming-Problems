#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
    //fastIO();
    lli n; cin>>n;
    if(n&1)
    {
        cout<<"Either\n";
    }
    else
    {
        n/=2;
        if(n&1)
        {
            cout<<"Odd\n";
        }
        else
        {
            cout<<"Even\n";
        }
    }

    return 0;
}