#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct Edge{
    lli v;
    Edge(lli v): v(v) {}
    Edge(): v(0) {}
};

vector< vector< Edge* > > adjList;
vector<lli> chainHead, depth, parent, szTree, tailChain, nextTo;
lli cnt = 0;
lli n; 

void addEdge(lli u, lli v)
{
    Edge* uv = new Edge(v);
    Edge* vu = new Edge(u);
    adjList[u].push_back(uv);
    adjList[v].push_back(vu);
}

void prep(lli n)
{
    adjList.resize(n+1);
    chainHead.resize(n+1);
    depth.resize(n+1, 0);
    parent.resize(n+1);
    szTree.resize(n+1);
    tailChain.resize(n+1);
    nextTo.resize(n+1, -1);
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

    lli maxSize = -1, index = -1;
    for(Edge *E: adjList[u])
    {
        lli v = E->v;
        if( v != parent[u] && szTree[v] > maxSize)
        {
            maxSize = szTree[v];
            index = v;
        }
    }

    if(index != -1)
    {
        getHLD(index, chain);
        nextTo[u] = index;
    } 
    else tailChain[chain] = u;

    for(Edge *E: adjList[u])
    {
        lli v = E->v;
        if( v!= parent[u] && v != index)
        {
            getHLD(v, v);
        }
    }
}


lli query(lli type, lli u)
{
    lli res;
    if(type == 1) cout << "d " << u << endl;
    else cout << "s " << u << endl;
    cin>>res;
    cout.flush();
    return res;
}



int main()
{
    //fastIO();
    lli n; cin>>n;
    prep(n);
    forn(i,0,n-1)
    {
        lli u, v; cin>>u>>v;
        addEdge(u,v);
    }
    dfs(1,1);
    getHLD(1,1);
   

    lli root = 1;
    lli depthX = query(1, root);
    while(true)
    {
        if(depthX == 0)
        {
            cout << "! " << root << endl;
            return 0;
        }
        lli v = tailChain[ chainHead[root] ], depthV = depth[v];
        lli dist = query(1,v);
        if(dist == 0)
        {
            cout << "! " << v << endl;
            return 0;
        }
        lli depthLCA = (depthV + depthX - dist)/2;
        for(int i = depth[root]; i<depthLCA; i++)
        {
            root = nextTo[root];
        }
        //root es el LCA de x y v
        if(depth[root] == depthX)
        {
            cout << "! " << root << endl;
            return 0;
        }
        root = query(2, root);
    }
    
    return 0;
}