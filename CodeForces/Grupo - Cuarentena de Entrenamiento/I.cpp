#include <bits/stdc++.h>
#define lli long long int 
#define endl "\n"

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n, m; cin>>n>>m;
    vector< pair<lli,vector<lli> >  > check(n);
    vector<lli> res(n,1);
    for(int i = 0; i<m; i++)
    {
        lli x, y; cin>>x>>y;
        x--,y--;
        check[x].first++;
        check[x].second.push_back(y);
        check[y].first++;
        check[y].second.push_back(x);
    }
    lli minimo=1000000000000000LL;
    for(auto x: check)
    {
        minimo = min(minimo, x.first);
    }
    for(int i = 0; i<n; i++)
    {
        pair< lli,vector<lli> > x = check[i];
        if(x.first == minimo)
        {
            res[i] = 0;
            for(auto y: x.second)
            {
                res[y] = 0;
            }
            break;
        }
    }

    for(auto x: res)
    {
        cout<<x<<" ";
    }


    return 0;
}
