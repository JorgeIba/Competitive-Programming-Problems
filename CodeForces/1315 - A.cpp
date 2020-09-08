#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"


using namespace std;

void solve()
{
    lli a, b, x, y; cin>>a>>b>>x>>y;
    lli ab = (a-1-x)*(b);
    lli arr = (x)*(b);
    lli der = (b-1-y)*(a);
    lli izq = (y)*a;
    lli res = max({ab,arr,der,izq});
    cout<<res<<endl;

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }

    return 0;
}