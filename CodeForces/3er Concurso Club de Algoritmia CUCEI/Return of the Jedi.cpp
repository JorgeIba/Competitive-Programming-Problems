#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<ld> intensity;
vector<ld> cost;
lli n; 

ld check(ld mid)
{
    ld total = 0;
    for(int i = 0; i<n; i++)
    {
        total += abs(intensity[i] - mid)*cost[i];
    }
    return total;
}

ld INF = 1e18;
const ld eps = 0.00001;

void solve()
{
    cin>>n;
    ld k; cin>>k;
    intensity.clear(); intensity.resize(n);
    cost.clear(); cost.resize(n);

    for(auto &x: intensity)
        cin>>x;
    for(auto &x: cost)
        cin>>x;
    
    ld l=0, r = INF;
    ld res = INF;
    while(l<=r)
    {
        ld mid = l + (r-l)/2;
        res = min(res, check(mid));
        if(check(mid + 0.00001) < check(mid - 0.00001))
        {
            l = mid+ 0.00001;
        }
        else
        {
            r = mid - 0.00001;
        }
    }
    cout<<fixed<<setprecision(4)<<res<<endl;
    if( k-res >= eps)
    {
        cout<<"May the Force be with you\n";
    }
    else
    {
        cout<<"It's a trap!\n";
    }
    //cout<<res<<endl;
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