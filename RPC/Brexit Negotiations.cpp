#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli INF = numeric_limits<int>::max();

vector<lli> visited;
vector<lli> maximos;
vector<lli> dependency;
vector<lli> minutes;
vector< vector<lli> > adj;

lli dfs(lli u)
{
    if(visited[u]) return maximos[u];
    visited[u] = true;
    maximos[u] = minutes[u];
    for(auto &x: adj[u])
    {
        maximos[u] = max(maximos[u], dfs(x));
    }
    return maximos[u];
}

int main()
{
    fastIO();
    lli n; cin>>n;
    visited.resize(n+1); maximos.resize(n+1, 0); dependency.resize(n+1); minutes.resize(n+1); adj.resize(n+1);
    priority_queue< pair<lli,lli> > q;

    forn(i, 1, n+1)
    {
        lli m, d; cin>>m>>d;
        dependency[i] = d;
        minutes[i] = m;
        forn(j,0,d)
        {
            lli v; cin>>v;
            adj[v].push_back(i);
        }
    }

    forn(i, 1, n+1)
    {
        dfs(i);
    }

    for(int i = 1; i<=n ; i++)
    {
        if(!dependency[i])
        {
            q.push({maximos[i], i});
        }
    }


    vector< pair<lli,lli> > order;
    while(!q.empty())
    {
        lli u =  q.top().second, m =  q.top().first;
        q.pop();
        order.push_back({u,m});
        for(auto p: adj[u])
        {
            if(p != 0 && (--dependency[p] == 0))
            {
                q.push({maximos[p], p});
            }
        }
    }

    lli maxi = -INF, cont = 0;
    for(auto x: order)
    {
        lli aux = x.second + (cont++);
        maxi=max(maxi,aux);
        //cout<<x.first<<" ";
    }
    cout<<maxi<<endl;


    return 0;
}