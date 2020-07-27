#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< lli > turistas;
vector< vector< lli > > adjList;
lli S, T;
lli n, m, k; 
const lli INF = 1e18;

typedef pair<lli,lli> pll;
bool check(lli x)
{
    vector< lli > dist(n+1, INF );
    vector<bool> visited( n+1 );
    priority_queue< pll, vector<pll>, greater<pll> > q;
    q.push({0,S});
    dist[S] = 0;
    while(!q.empty())
    {
        lli u = q.top().second; q.pop();
        for(auto v: adjList[u])
        {
            if(dist[u] + 1 <= x && dist[u] + 1 < dist[v])
            {
                if(turistas[v])
                {
                    q.push({0, v});
                    dist[v] = 0;
                }
                else
                {
                    q.push( {dist[u]+1, v} );
                    dist[v] = dist[u] + 1;
                }
            }
        }
    }

    if(dist[T] <= x)
    {
        return true;
    }
    return false;
    
}


void prep(lli n)
{
    adjList.resize(n+1);
    turistas.resize(n+1);
}

int main()
{
    fastIO();
    cin>>n>>m>>k;
    prep(n);
    for(int i = 0; i<k; i++) 
    {
        lli x; cin>>x;
        turistas[x] = true;
    }

    for(int i = 0; i<m; i++)
    {
        lli u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    cin>> S >> T;
    
    //cout << check(3) << endl;

    
    lli l = 0, r = m+100, res = -1;
    while(l <= r)
    {
        lli mid = l + (r-l)/2;
        if( check(mid)   )
        {
            res = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }

    cout << res << endl;   
    
    return 0;
}