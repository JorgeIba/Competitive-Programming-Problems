#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;


struct Edge{
    lli to, cost;
    Edge(): to(0), cost(0) {}
    Edge(lli to, lli cost): to(to), cost(cost) {}
};

struct Query{
    lli l, r, idx;
    Query(): l(0), r(0), idx(0) {}
    Query(lli l, lli r, lli idx): l(l), r(r), idx(idx) {}
};

const lli INF = 1e16 + 10;
vector< vector< Edge* > > adjList;
vector< lli > parent, szTree, costos, ans, ST, lazy;
vector< vector< Query* > > queries;
lli n, q; 


void build(lli id, lli l, lli r)
{
    if(l==r)
    {
        ST[id] = costos[l]; return;
    }
    lli mid = l + (r-l)/2;
    build(2*id, l, mid);
    build(2*id + 1, mid+1, r);
    ST[id] = min(ST[2*id], ST[2*id+1]);
}

//10
void propagate(lli id, lli l, lli r, lli value)
{
    ST[id] += value;
    if(l!=r)
    {
        lazy[2*id] += value;
        lazy[2*id + 1] += value;
    }
}
//16
void update(lli id, lli l, lli r, lli start, lli end, lli value)
{
    if(lazy[id] != 0){
        propagate(id, l, r, lazy[id]);
        lazy[id] = 0;
    }
    if( end < l || r < start) return;
    if ( start <= l && r <= end) propagate(id, l, r, value);
    else{
        lli mid = (l+r)/2;
        update(2*id, l, mid, start, end, value);
        update(2*id+1, mid+1, r, start, end, value);
        ST[id] = min(ST[2*id], ST[2*id + 1]);
    }
}
//14
lli query(lli id, lli l, lli r, lli start, lli end) 
{
    if(lazy[id] != 0){
        propagate(id, l, r, lazy[id]);
        lazy[id] = 0;
    }
    if( end < l || r < start) return INF;
    if ( start <= l && r <= end  ) return ST[id];
    else{
        lli mid = l + (r-l)/2;
        return min(query(2*id, l, mid, start, end), query(2*id+1, mid+1, r, start, end));
    }
}

void addEdge(lli u, lli v, lli cost)
{
    Edge *uv = new Edge(v, cost);
    adjList[u].push_back(uv);
}

void dfs(lli u, lli cost)
{
    szTree[u] = 1;
    if(adjList[u].size() == 0) // Hoja
        costos[u] = cost;

    for(Edge* E: adjList[u])
    {
        lli v = E->to, c = E->cost;
        if( v != parent[u])
        {
            dfs(v, cost + c);
            szTree[u] +=  szTree[v];
        }
    }
}

void go(lli u, lli cost)
{
    for(Query *Q: queries[u])
    {
        ans[Q->idx] = query(1, 1, n, Q->l, Q->r);
        //cout << u << " " << Q->l << "--" << Q->r << endl;
    }

    for(Edge* E: adjList[u])
    {
        lli v = E->to, c = E->cost;
        if(v != parent[u])
        {
            lli l = v, r = v + szTree[v] - 1;
            //cout << v << endl;
            update(1, 1, n, 1, n, c);    // Agregar a todos cost
            update(1, 1, n, l, r, -2*c);// quitar a l, r 2*cost
            go(v, c);
            update(1, 1, n, 1, n, -c);
            update(1, 1, n, l, r, 2*c);
        }
    }
}

void prep(lli n, lli q)
{
    adjList.resize(n+1);
    parent.resize(n+1);
    szTree.resize(n+1);
    costos.resize(n+1, INF);
    queries.resize(n+1);
    ans.resize(q+1);
    ST.resize(4*(n+1), INF);
    lazy.resize(4*(n+1));
}

int main()
{
    fastIO();
    cin>>n>>q;
    prep(n, q);
    for(int i = 2; i<=n; i++)
    {
        lli cost;
        cin >> parent[i] >> cost;
        addEdge(parent[i], i, cost);
    }

    dfs(1, 0);

    for(int i = 0; i<q; i++)
    {
        lli u, l, r; cin>>u>>l>>r;
        Query* Q = new Query(l, r, i);
        queries[u].push_back(Q);
    }
    build(1, 1, n);
    go(1, 0);
    
    for(int i = 0; i<q; i++)
    {
        cout << ans[i] << endl;
    }

    return 0;
}