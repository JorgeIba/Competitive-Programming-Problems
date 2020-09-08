#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;
lli n, q; 

struct Edge
{
    lli to, flow, capacity, idx, cost;
    Edge* res;
    Edge(lli to, lli capacity, lli cost): to(to), flow(0), capacity(capacity), cost(cost) {}

    void addFlow(lli flow)
    {
        this->flow += flow;
        this->res->flow -= flow;
    }
};

vector< vector<Edge*> > adjList;
vector< lli > dis, pos;
const lli INF = numeric_limits<int>::max();

void addEdge(lli u, lli v, lli capacity, lli cost)
{
    Edge* uv = new Edge(v, capacity, cost);
    Edge* vu = new Edge(u, 0, cost);
    uv->res = vu;
    vu->res = uv;
    adjList[u].push_back(uv);
    adjList[v].push_back(vu);
}

const lli maxV = 10000;

pair<lli, lli> maxFlowMinCost(int s, int t)
{
    vector<bool> inQueue(maxV);
    vector<lli> distance(maxV), cap(maxV);
    vector<Edge*> parent(maxV);
    lli maxFlow = 0, minCost = 0;
    while(true){
        fill(distance.begin(), distance.end(), INF);
        fill(parent.begin(), parent.end(), nullptr);
        fill(cap.begin(), cap.end(), 0);
        distance[s] = 0;
        cap[s] = INF;
        queue<int> Q;
        Q.push(s);
        while(!Q.empty()){
            int u = Q.front(); Q.pop(); inQueue[u] = 0;
            for(Edge *v : adjList[u]){
                if(v->capacity > v->flow && distance[v->to] > distance[u] + v->cost){
                    distance[v->to] = distance[u] + v->cost;
                    parent[v->to] = v;
                    cap[v->to] = min(cap[u], v->capacity - v->flow);
                    if(!inQueue[v->to]){
                        Q.push(v->to);
                        inQueue[v->to] = true;
                    }
                }
            }
        }
        if(!parent[t]) break;
        maxFlow += cap[t];
        minCost += cap[t] * distance[t];
        for(int u = t; u != s; u = parent[u]->res->to)
            parent[u]->addFlow(cap[t]);
    }
    return {maxFlow, minCost};
}

void prep(lli n)
{
    adjList.resize(2*(n+2));
    dis.resize(2*(n+2));
    pos.resize(2*(n+2));
}

void solve(vector< pair<lli,lli> > &nums) // 1 - (n) arreglo, 1+n - (n+n) , ((2*n+1)*i ) 2*n+1 S, 2*n + 2 T
{
    prep(maxV);

    for(int i = 1; i<=n; i++)
    {
        for(int j = nums[i-1].first; j<=nums[i-1].second; j++)
        {
            addEdge(i, j + n, 1, 0);
        }
    }

    lli S = 0 , T = n*n + 3*n - 1;
    for(int i = 1; i<=n; i++)
    {
        for(int k = 1; k<=n; k++)
        {
            addEdge(i+n, (i+1)*n + k, 1, 2*k-1);
            addEdge((i+1)*n + k, T, INF, 0);
        }
        
    }
    
    for(int i = 1; i<=n; i++)
    {
        addEdge(S, i, 1, 0);
    }
    
    cout << maxFlowMinCost(S, T).second << endl;

}

int main()
{
    fastIO();
    cin>>n>>q;
    vector< pair<lli,lli> > nums(n);
    for(int i = 0; i<n; i++)
    {
        nums[i] = {1,n};
    }
    while(q--)
    {
        lli t, l, r, v; cin>>t>>l>>r>>v;
        l--, r--;
        if(t == 1)
        {
            for(int i = l; i<=r; i++)
            {
                nums[i].first = max(nums[i].first, v);
            }
        }
        else
        {
            for(int i = l; i<=r; i++)
            {
                nums[i].second = min(nums[i].second, v);
            }
        }
    }

    for(int i = 0; i<n; i++)
    {
        if(nums[i].first > nums[i].second)
        {
            cout << -1 << endl; return 0;
        }
    }

    solve(nums);
    
    return 0;
}