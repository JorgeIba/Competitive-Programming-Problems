#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

/*
    When all capacities are the unity: O(n*sqrt(n))
    General without scaling: O(V^2*E)
    General with scaling:  O(E*V*log(U)) where U is maximum flow
*/

struct Edge{
    lli to, flow, capacity;
    Edge* res;
    Edge(int to, lli capacity, lli cost = 0): to(to), flow(0), capacity(capacity) {}
    void addFlow(lli flow)
    {
        this->flow += flow;
        this->res->flow -= flow;
    }
};
struct Dinic{
    vector< vector< Edge* > > adjList;
    vector< int > pos, dist;
    lli N;
    lli limit = 1;
    bool scaling;
    const lli INF = numeric_limits<lli>::max();

    Dinic(lli N, bool withScaling = false): N(N), scaling(withScaling) {
        adjList.resize(N);
        pos.resize(N);
        dist.resize(N);
    }

    void addEdge(int u, int v, lli capacity, bool directed = true)
    {
        Edge* uv = new Edge(v, capacity);
        Edge* vu = new Edge(u, directed?0:capacity); // change 0 for capacity if is undirected
        uv->res = vu;
        vu->res = uv;
        adjList[u].push_back(uv);
        adjList[v].push_back(vu);
    }

    lli BlockingFlow(int u, int t, lli flow)
    {
        if(u == t) return flow;
        for(int &i= pos[u]; i<(int)adjList[u].size(); i++ )
        {
            Edge* E = adjList[u][i];
            if(E->capacity > E->flow && dist[E->to] == dist[u] + 1)
            {
                lli f = BlockingFlow(E->to, t, min(flow, E->capacity - E->flow));
                if(f>0)
                {
                     E->addFlow(f); 
                     return f;
                }
            }
        }
        return 0;
    }
    bool bfs(int s, int t)
    {
        fill(all(dist), -1);
        queue<lli> q; q.push(s);
        dist[s] = 0;
        while(!q.empty())
        {
            lli u = q.front(); q.pop();
            for(Edge* E: adjList[u])
            {
                if(dist[E->to] == -1 && E->capacity > E->flow && (!scaling || E->capacity - E->flow >= limit))
                {
                    dist[E->to] = dist[u] + 1;
                    q.push(E->to);
                }
            }
        }
        return dist[t] != -1;
    }
    
    lli StartDinic(int s, int t)
    {
        lli maxFlow = 0;
        for(limit = (scaling?1<<30:1); limit>0; limit>>=1) // (1<<30) is for maximum capacity = 10^9
        {
            dist[t] = 0;
            while(bfs(s, t))
            {
                int f = 0;
                fill(all(pos), 0);
                while((f = BlockingFlow(s, t, INF)))
                {
                    maxFlow += f;
                }
            }
        }
        return maxFlow;
    }
};

#define point pair<lli,lli>
#define x first
#define y second

const int maxA = 1e8+5, INF = 1e9;
vector<point> student, professor;

lli distance(const point &a, const point &b)
{
    return abs(a.x - b.x) + abs(a.y-b.y);
}

bool check(lli mid)
{
    int n = SZ(student);
    Dinic D(2*(n+1));
    int s = 2*n, t = 2*n + 1;

    for(int i = 0; i<n; i++)
    {
        D.addEdge(s, i, true);
        D.addEdge(i+n, t, true);

        for(int j = 0; j<n; j++)
        {
            if(distance(student[i], professor[j]) <= mid)
            {
                D.addEdge(i, j+n, INF);
            }
        }
    }

    return D.StartDinic(s,t) == n;
}



int main () {
	fastIO();
    lli n; cin>>n;
    student.resize(n);
    professor.resize(n);

    for(auto &p: student) cin>>p.x>>p.y;
    for(auto &p: professor) cin>>p.x>>p.y;

    lli l = 0, r = 4*maxA, ans = 0;
    while(l<=r)
    {
        lli mid = l + (r-l)/2;
        if(check(mid))
        {
            ans = mid;
            r = mid-1;
        }
        else
        {
            l = mid+1;
        }
    }

    cout << ans << endl;

    
	return 0;
}