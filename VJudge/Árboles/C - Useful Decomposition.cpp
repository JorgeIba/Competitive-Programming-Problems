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
    forn(i,0,n-1)
    {
        lli u, v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    lli cont = 0, root =  -1;
    vector< lli > hojas;
    for(int i = 1; i<=n; i++)
    {
        if(adj[i].size() > 2)
        {
            cont++;
            root = i;
        }  
        if(adj[i].size() == 1)
        {
            hojas.push_back(i);
        }
    }
    if(cont > 1)
    {
        cout<<"No\n"; return 0;
    }
    cout<<"Yes\n";
    if(cont == 0)
    {
        cout<<1<<endl;
        assert(hojas.size() == 2);
        cout<< hojas[0] <<" " << hojas[1] << endl;
        return 0;
    }
    else
    {
        cout<<hojas.size()<<endl;
        for(auto x: hojas)
        {
            cout<<root<<" "<<x<<endl;
        }
    }
    

    return 0;
}