#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct Edge{
    lli v, c; 
    Edge(lli v, lli c): v(v), c(c) {}
    Edge(): v(0), c(0) {}
};

vector< vector< Edge* > > adjList;
vector< lli > chainHead, parent, depth, idST, szTree, degree, ST, lazy;
lli cnt = 0;
lli n, q;

//10
void propagate(lli id, lli l, lli r, lli value)
{
    if(value == -1) ST[id] = 0;
    else ST[id] = (r-l+1)*value; //Suma
    if(l!=r)
    {
        lazy[2*id] = value;
        lazy[2*id + 1] = value;
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
        ST[id] = ST[2*id] + ST[2*id + 1];
    }
}
//14
lli query(lli id, lli l, lli r, lli start, lli end) 
{
    if(lazy[id] != 0){
        propagate(id, l, r, lazy[id]);
        lazy[id] = 0;
    }
    if( end < l || r < start) return 0;
    if ( start <= l && r <= end  ) return ST[id];
    else{
        lli mid = l + (r-l)/2;
        return query(2*id, l, mid, start, end) + query(2*id+1, mid+1, r, start, end);
    }
}


void addEdge(lli u, lli v)
{
    Edge* uv = new Edge(v, 0);
    Edge* vu = new Edge(u, 0);
    adjList[u].push_back(uv);
    adjList[v].push_back(vu);
}

void prep(lli n)
{
    adjList.resize(n+1);
    chainHead.resize(n+1);
    parent.resize(n+1);
    depth.resize(n+1);
    idST.resize(n+1);
    szTree.resize(n+1);
    degree.resize(n+1);
    ST.resize(4*n);
    lazy.resize(4*n);
}

void dfs(lli u, lli p)
{
    szTree[u] = 1;
    parent[u] = p;
    for(Edge* E: adjList[u])
    {
        lli v = E->v;
        if( v!= p)
        {
            depth[v] = depth[u] + 1;
            dfs(v,u);
            szTree[u] += szTree[v];
        }
    }
}


void getHLD(lli u, lli chain)
{
    chainHead[u] = chain;
    idST[u] = cnt++;

    lli maxSize = -1, index = -1;
    for(Edge *E: adjList[u])
    {
        lli v = E->v;
        if(v != parent[u] && szTree[v] > maxSize)
        {
            maxSize = szTree[v];
            index = v;
        }
    }

    if(index != -1)
    {
        getHLD(index, chain);
    }
    for(Edge *E: adjList[u])
    {
        lli v = E->v;
        if( v != parent[u] && v != index)
        {
            getHLD(v, v);
        }
    }
}


lli queryU(lli u, lli v)
{
    lli res = 0;
    u = parent[u], v = parent[v];
    while(  chainHead[u] != chainHead[v]  )
    {
        if(  depth[ chainHead[u] ]  < depth[ chainHead[v] ] ) swap(u,v);
        res += query(1, 1, n, idST[ chainHead[u] ] + 1, idST[u] + 1 );
        u = parent[chainHead[u]];
    }

    if( depth[u] > depth[v]) swap(u,v);

    res += query(1, 1, n, idST[u]+1, idST[v]+1);
    return res;
}


void updateU(lli u, lli v, lli value)
{
    u = parent[u], v = parent[v];
    while(  chainHead[u] != chainHead[v]  )
    {
        if(  depth[ chainHead[u] ]  < depth[ chainHead[v] ] ) swap(u,v);
        update(1, 1, n, idST[ chainHead[u] ] + 1, idST[u] + 1, value);
        u = parent[chainHead[u]];
    }

    if( depth[u] > depth[v]) swap(u,v);

    update(1, 1, n, idST[u]+1, idST[v]+1, value);
}



int main()
{
    fastIO();
    cin>>n>>q;
    prep(n);
    for(int i = 0; i<n-1; i++)
    {
        lli u, v; cin>>u>>v;
        addEdge(u,v);
        degree[u] ++;
        degree[v] ++;
    }
    lli root = -1;
    for(int i = 1; i<=n; i++)
    {
        if(degree[i] > 1)
        {
            root = i;
            break;
        }
    }

    dfs(root,root);
    getHLD(root,root);

    while(q--)
    {
        lli u, v, x, y; cin>>u>>v>>x>>y;
        updateU(u,v, 1);
        cout << queryU(x,y) << endl;
        update(1, 1, n, 1, n, -1);
    }

    return 0;
}