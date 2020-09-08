#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;


int main()
{
    fastIO();
    lli n; cin>>n;
    vector< vector< lli > > adj(n+1);
    for(int i = 2; i<=n; i++)
    {
        lli p; cin>>p;
        adj[i].push_back(p);
        adj[p].push_back(i);
    }
    for(int i = 1; i<=n; i++)
    {
        lli cont = 0;
        if(adj[i].size() == 1 ) continue; //leaf

        for(auto v: adj[i])
        {
            if( adj[v].size() == 1)
            {
                cont++;
            }
        }
        if(cont<3)
        {
            cout<<"No\n";
            return 0;
        }
    }
    cout<<"Yes\n";
    return 0;
}