#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

lli n; 
vector<lli> a, b, c;
vector< vector<lli> > adj;
vector< pair<lli,lli> > cont; // type1, type2
vector<lli> visited;
lli ans = 0;

void init()
{
    a.resize(n); b.resize(n); c.resize(n); adj.resize(n); cont.resize(n);
    visited.resize(n, false);
}


pair<lli,lli> dfs(lli idx)
{
    assert(!visited[idx]);
    visited[idx] = true;
    for(auto v: adj[idx])
    {
        if(!visited[v])
        {
            pair<lli,lli> aux = dfs(v);
            cont[idx].first += aux.first;
            cont[idx].second += aux.second;
        }
    }

    lli minimo = min(cont[idx].first, cont[idx].second);
    //cout<<idx<<" "<<minimo<<endl;
    ans+= 2*minimo*a[idx];
    cont[idx].first -= minimo;
    cont[idx].second -= minimo;

    return cont[idx];
}




int main()
{
    fastIO();
    cin>>n;
    init();
    lli type1 = 0, type2 = 0;
    for(int i = 0; i<n; i++)
    {
        cin>>a[i]>>b[i]>>c[i];
        if(b[i] == 0 && c[i] == 1)
        {
            type1++;
            cont[i] = {0, 1};
        }
        else if(b[i] == 1 && c[i] == 0)
        {
            type2++;
            cont[i] = {1, 0};
        }
        else
        {
            cont[i] = {0,0};
        }
    }

    for(int i = 0; i<n-1; i++)
    {
        lli u, v; cin>>u>>v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if(type1 != type2)
    {
        cout<<-1<<endl;
        return 0;
    }
    
    vector<lli> dist(n,-1);
    queue<lli> q;
    q.push(0);
    dist[0] = 0;
    while(!q.empty())
    {
        lli u = q.front(); q.pop();
        for(auto v: adj[u])
        {
            if(dist[v] == -1)
            {
                a[v] = min(a[v], a[u]);
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    dfs(0);

    cout<<ans<<endl;



    return 0;
}