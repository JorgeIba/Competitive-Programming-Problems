#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

bool isPerfectSquare(lli n)
{
    lli r = sqrt(n);
	return r * r == n;
}

int main()
{
    //fastIO();
    lli n; cin>>n;
    if(n&1)
    {
        if(n*n - 1 - 2*n > 0)
        {
            cout<<"Yes, YOU CAN";
            return 0;
        }
    }
    else
    {
        if(n*n - 4*n - 4 > 0)
        {
            cout<<"Yes, YOU CAN";
            return 0;
        }
    }
    cout<<"No, PLEASE LET ME GO";
    
    return 0;
}