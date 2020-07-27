#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

lli n; 
const lli INF = 1e18;
vector< lli > chainHead, idST, depth, szTree, costArray, ST, parent, specialChild;
vector< pair<lli,lli> > indexEdges;
lli cnt = 0;


//12
void build() //ST size == 2*n
{
    for(int i = n; i<2*n; i++)
    {
        ST[i] = costArray[i-n];
    }
    for(int i = n-1; i>0; i--)
    {
        ST[i] = max( ST[i<<1] , ST[i<<1|1] ) ;
    }
}
//11
lli query(lli l, lli r) 
{
    lli MAX1 = -INF;
    lli MAX2 = -INF;
    for(l+=n, r+=n; l<=r; l>>=1, r>>=1)
    {
        if(l&1) MAX1 = max(MAX1, ST[l++]);   
        if(~r&1) MAX2 = max(ST[r--],MAX2);
    }
    return max(MAX1, MAX2);
}
//10
void update(int index, lli value)
{
    index+=n;
    ST[index] = value;
    for(; index; index>>=1)
    {
        ST[index>>1] = max(ST[index], ST[index^1]);
    }
}


struct Edge
{
    lli v, c;
    Edge(lli v, lli c): v(v), c(c) {}
    Edge(): v(0), c(0) {}
};

vector< vector< Edge* > > adjList;

void addEdge(lli u, lli v, lli c)
{
    Edge *uv = new Edge(v, c);
    Edge *vu = new Edge(u, c);
    adjList[u].push_back(uv);
    adjList[v].push_back(vu);
}

void dfs(lli u, lli p)
{
    szTree[u] = 1;
    parent[u] = p;
    for(Edge* E: adjList[u])
    {
        lli v = E->v, c = E->c;
        if( v != p)
        {
            depth[v] = depth[u] + 1;
            dfs(v,u);

            szTree[u] += szTree[v];
        }
    }
}

void getHLD(lli u, lli cost, lli chain)
{
    chainHead[u] = chain;
    idST[u] = cnt;
    costArray[ cnt++ ] = cost;

    lli maxSize = -1, index = -1, costMax=-1;
    for(Edge* E: adjList[u])
    {
        lli v = E->v, c = E->c;
        if(szTree[v] > maxSize && v != parent[u])
        {
            maxSize = szTree[v];
            index = v;
            costMax = c;
        }
    }

    if(maxSize != -1) //No es nodo hoja
    {
        getHLD(index, costMax, chain);
        specialChild[u] = index;
    }
        

    for(Edge* E: adjList[u])
    {
        lli v = E->v, c = E->c;
        if(v != index &&  v != parent[u])
        {
            getHLD(v, c, v);
        }
    }
}


void prep()
{
    adjList.clear(); adjList.resize(n+1);
    chainHead.clear(); chainHead.resize(n+1);
    idST.clear(); idST.resize(n+1);
    depth.clear(); depth.resize(n+1);
    szTree.clear(); szTree.resize(n+1);
    costArray.clear(); costArray.resize(n+1);
    ST.clear(); ST.resize(2*(n+1));
    parent.clear(); parent.resize(n+1);
    indexEdges.clear(); indexEdges.resize(n+1);
    specialChild.clear(); specialChild.resize(n+1);
    cnt = 0;
}


lli queryU(lli u, lli v)
{
    lli res = -INF;
    while( chainHead[u] != chainHead[v]  )
    {
        if( depth[  chainHead[u]  ] < depth[   chainHead[v]  ] ) swap(u,v);
        res = max(res, query(  idST[ chainHead[u]  ] , idST[u]   ));
        //cout<< u << " " << chainHead[u]<<endl;
        u = parent[ chainHead[u] ];
    }

    if( depth[u] > depth[v]) swap(u,v); 

    //En este punto, u es el LCA.

    u = specialChild[u];
    res = max( res,  query( idST[u], idST[v]  ));
    return res;
}

void updateU(lli i, lli x)
{
    lli u = indexEdges[i-1].first, v = indexEdges[i-1].second;
    if( u == parent[v] )
    {
        update(idST[ v ], x);
    }
    else
    {
        update(idST[ u ], x);
    }
}


void solve()
{
    cin>>n;
    prep();
    for(int i = 0; i<n-1; i++)
    {
        lli u, v, c; cin>>u>>v>>c;
        addEdge(u,v,c);
        indexEdges[i] = {u,v};
    }

    dfs(1, 1);
    getHLD(1, -INF, 1);
    build();

    while(true)
    {
        string s; cin>>s;
        if(s == "QUERY")
        {
            lli u, v; cin>>u>>v;
            if(u == v) 
            {
                cout<< 0 << endl;
                continue;
            }
            cout << queryU(u,v) << endl;
        }
        else if( s == "CHANGE")
        {
            lli i, x; cin>>i>>x;
            updateU(i, x);
        }
        else
        {
            break;
        }
    }

}



int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--) solve();

    return 0;
}