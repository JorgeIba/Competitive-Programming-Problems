#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< lli > alt;
vector<vector<lli>> adj;
const lli INF = 1e9 + 7;
vector<lli> visited;

bool dfs(lli index, lli target, lli &maximo, lli &minimo)
{
    if(index == target)
    {
        maximo = max(maximo, alt[index]);
        minimo = min(minimo, alt[index]);
        return true;
    } 
    if(visited[index]) return false;
    visited[index] = true;
    for(auto x: adj[index])
    {
        if(dfs(x, target, maximo, minimo))
        {
            maximo = max(maximo, alt[index]);
            minimo = min(minimo, alt[index]);
            return true;
        }
    }
    return false;
}




int main()
{
    fastIO();
    lli n; cin>>n;
    alt.resize(n);
    adj.resize(n);
    visited.resize(n);
    for(auto &x: alt)
    {
        cin>>x;
    }
    forn(i, 0, n-1)
    {
        lli x, y; cin>>x>>y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    lli q; cin>>q;
    while(q--)
    {
        lli i, f; cin>>i>>f;
        i--, f--;
        lli ma = -INF;
        lli mi = INF;
        visited.clear();
        visited.resize(n);
        dfs(i, f, ma, mi);
        cout<< (ma-mi) <<endl;
    }

    return 0;
}