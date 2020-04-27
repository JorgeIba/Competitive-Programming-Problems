#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void solve()
{
    lli n, a, b, c, d; cin>>n>>a>>b>>c>>d;
    lli minimo = (a-b)*n;
    lli maximo = (a+b)*n;
    lli minimoo = (c-d);
    lli maximoo = (c+d);

    if( maximo < minimoo || minimo > maximoo  )
    {
        cout<<"No\n";
    }
    else
    {
        cout<<"Yes\n";
    }

}


int main()
{
    lli t;
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}