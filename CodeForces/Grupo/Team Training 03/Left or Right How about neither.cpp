#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

lli n, l, r, c; 
vector<lli> nums;
vector< vector< pair<lli,lli> > > adj;
map<lli, vector<lli> > colors;

void addEdge(lli u, lli i, lli cost)
{
    adj[u].push_back({ i, cost});
}


void build()
{
    for(int i = 1; i<n; i++)
    {
        addEdge(i,i-1, l);
        addEdge(i-1, i, r);
    }

    lli idx = n;
    for(auto p: colors)
    {
        for(auto x: p.second)
        {
            addEdge(x, idx, c/2);
            lli toComplete = c/2; toComplete = c - toComplete;
            addEdge(idx, x, toComplete);
        }
        idx++;
    }
}

const lli INF = numeric_limits<lli>::max();

typedef pair<lli,lli> pll;
vector<lli> dist;
lli dijkstra(lli from, lli to) //n-> adj size
{
    dist.resize( adj.size(), INF );
    vector<bool> visited( adj.size() );

    priority_queue< pll, vector<pll>, greater<pll> > q;
    q.push({0,from});
    dist[from] = 0;
    while(!q.empty())
    {
        lli u = q.top().second; q.pop();
        if(visited[u]) continue;
        visited[u] = true;
        for(auto v: adj[u])
        {
            if(dist[u] + v.second < dist[v.first])
            {
                dist[v.first] = dist[u] + v.second;
                q.push({ dist[v.first], v.first});
            }
        }
    }
    return dist[to];
}


int main()
{
    fastIO();
    cin>>n>>l>>r>>c;
    lli from, to; cin>>from>>to;
    from--,to--;
    nums.resize(n);
    for(int i = 0; i<n; i++)
    {
        cin>>nums[i];
        nums[i]--;
        colors[ nums[i] ].push_back(i);
    }
    adj.resize( n+colors.size()  );
    build();
    
    lli res = dijkstra(from, to);
    cout<<res<<endl;

    return 0;
}