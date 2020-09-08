#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

void solve()
{
    lli n, x; cin>>n>>x;
    x--;
    vector<lli> degree(n);
    vector< vector<lli> > adj(n);
    vector<lli> dist(n, -1);
    for(int i = 0; i<n-1; i++)
    {
        lli u, v; cin>>u>>v;
        u--,v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        degree[u]++;
        degree[v]++;
    }

    if(degree[x] <= 1)
    {
        cout<<"Ayush\n";
        return;
    }
    
    queue<lli> q;
    q.push(x);
    dist[x] = 0;

    while(!q.empty())
    {
        lli u = q.front(); q.pop();
        for(auto v: adj[u])
        {
            if(dist[v] == -1)
            {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    lli contador = 0, contadorAA=0;
    for(auto x: dist)
    {
        if(x>=2)
        {
            contador++;
        }
        else if(x==1)
        {
            contadorAA++;
        }
    }
    
    if( (contador+contadorAA-2) & 1) // if((n-3) & 1)
    {
        cout<<"Ayush\n";
    }
    else
    {
        cout<<"Ashish\n";
    }
}



int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}