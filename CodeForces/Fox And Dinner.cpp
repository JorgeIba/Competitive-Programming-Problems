#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<bool> isPrime;
void primesSieve(int n)
{
	isPrime.resize(n + 1, true);
	isPrime[0] = isPrime[1] = false;
	for(int i = 4; i <= n; i += 2) isPrime[i] = false;
	for(lli i = 3; i*i <= n; i += 2)
    {
		if(isPrime[i])
        {
			if(i * i <= n)
				for(int j = i * i; j <= n; j += 2 * i)
					isPrime[j] = false;
		}
	}
}

struct Edge
{
    lli to, flow, capacity;
    Edge *res;
    Edge(lli to, lli flow, lli capacity): to(to), flow(flow), capacity(capacity) {}

    void addFlow(lli flow)
    {
        this->flow += flow;
        this->res->flow -= flow;
    }
};

vector< vector<Edge*> > adjList;
vector< lli > pos;
vector< lli > dist;
vector<bool> visited;
lli n; 
const lli INF = numeric_limits<int>::max();



void addEdge(lli u, lli v, lli capacity)
{
    Edge *uv = new Edge(v, 0, capacity);
    Edge *vu = new Edge(u, 0, 0);
    uv->res = vu;
    vu->res = uv;
    adjList[u].push_back(uv);
    adjList[v].push_back(vu);
}




lli blockingFlow(lli u, lli t, lli flow)
{
    if(u==t) return flow;
    for(lli &i = pos[u]; i<adjList[u].size(); i++)
    {
        Edge *v = adjList[u][i];
        if(v->capacity > v->flow && dist[u] + 1 == dist[v->to])
        {
            lli fv = blockingFlow(v->to, t, min(flow, v->capacity - v->flow));
            if(fv > 0)
            {
                v->addFlow(fv);
                return fv;
            }
        }
    }
    return 0;
}



lli dinic(lli s, lli t)
{
    lli maxFlow = 0;
    dist[t] = 0;
    while(dist[t] != -1)
    {
        fill(all(dist), -1);
        queue<lli> q; q.push(s);
        dist[s] = 0;
        while(!q.empty())
        {
            lli u = q.front(); q.pop();
            for(Edge* v: adjList[u])
            {
                if(dist[v->to] == -1 && v->capacity > v->flow)
                {
                    dist[v->to] = dist[u] + 1;
                    q.push(v->to);
                }
            }
        }
        if(dist[t] != -1)
        {
            lli f = 0;
            fill(all(pos), 0);
            while(f = blockingFlow(s,t,INF))
            {
                maxFlow += f;
            }
        }
    }
    return maxFlow;
}


void dfs(lli u, vector< vector<lli> > &ans)
{
    if(visited[u]) return;
    visited[u] = true;
    ans[ans.size()-1].push_back(u);
    for(Edge *v: adjList[u])
    {
        if(abs(v->flow) == 1)
            dfs(v->to, ans);    
    }
}



int main()
{
    //fastIO();
    primesSieve(30000);
    cin>>n;
    adjList.resize(n+2);
    pos.resize(n+2);
    dist.resize(n+2);
    visited.resize(n+1);
    vector<lli> nums(n+1);
    forn(i,1,n+1) cin>>nums[i];
    //source -> 0, sink ->n+1
    // 0 -> impar, par -> n+1
    forn(i, 1, n+1) 
    {
        if(nums[i]&1) addEdge(0, i, 2);
        else addEdge(i,n+1,2);
    }
    for(int i = 1; i<=n; i++)
    {
        for(int j = i+1; j<=n; j++)
        {
            if(isPrime[nums[i] + nums[j]])
            {
                if(nums[i] & 1)
                {
                    addEdge(i,j,1);
                }
                else
                {
                    addEdge(j,i,1);
                }
            }
        }
    }

    if(dinic(0,n+1) != n)
    {
        cout<<"Impossible\n";
        return 0;
    }


    vector< vector<lli> > ans;
    for(int i = 1; i<=n; i++)
    {
        if(visited[i]) continue;
        else
        {
            ans.push_back({});
            dfs(i, ans);
        }
    }

    cout<<ans.size()<<endl;
    
    for(auto x: ans)
    {
        cout<<x.size()<<" ";
        for(auto a: x)
        {
            cout<<a<<" ";
        }
        cout<<endl;
    }


    return 0;
}