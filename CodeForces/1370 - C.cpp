#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;



void solve()
{
    lli n; cin>>n;
    if(n==1) 
    {
        cout<<"FastestFinger\n";
        return;
    }
    if(n&1 || n==2)
    {
        cout<<"Ashishgup\n";
    }
    else
    {
        lli cont = 0;
        while(~n&1)
        {
            cont++;
            n>>=1;
        }
        if(cont > 1 && n != 1)
        {
            cout<<"Ashishgup\n";
        }
        else
        {
            for(int i = 3; i*i<=n; i++)
            {
                if(n % i == 0)
                {
                    cout<<"Ashishgup\n";
                    
                    return;
                }
            }
            cout<<"FastestFinger\n";
        }
    }
}



int main()
{
    //fastIO();
    lli t; cin>>t;
    while(t--)
        solve();
    return 0;
}