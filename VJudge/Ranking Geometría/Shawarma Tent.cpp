#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
    fastIO();
    lli n, sx, sy; cin>>n>>sx>>sy;
    lli izq=0, der=0, arri=0, abaj=0;
    forn(i,0,n)
    {
        lli x, y; cin>>x>>y;
        if(x<sx) izq++;
        if(x>sx) der++;
        if(y>sy) arri++;
        if(y<sy) abaj++;
    }
    lli res = max({izq,der,arri,abaj});
    cout<<res<<endl;
    if(res == izq)
    {
        cout<<(sx-1)<<" "<<sy<<endl;
    }
    else if(res == der)
    {
        cout<<(sx+1)<<" "<<sy<<endl;
    }
    else if(res == abaj)
    {
        cout<<sx<<" "<<(sy-1)<<endl;
    }
    else
    {
        cout<<sx<<" "<<(sy+1)<<endl;
    }
    

    return 0;
}