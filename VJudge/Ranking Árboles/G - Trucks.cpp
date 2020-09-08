#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

typedef vector<int> vi;
typedef vector<bool> vb;
int inf = 1 << 30;



struct disjointSet{
	int N;
	vector<short int> rank;
	vi parent, count;

	disjointSet(int N): N(N), parent(N), count(N), rank(N){}

	void makeSet(int v){
		count[v] = 1;
		parent[v] = v;
	}

	int findSet(int v){
		if(v == parent[v]) return v;
		return parent[v] = findSet(parent[v]);
	}

	void unionSet(int a, int b){
		a = findSet(a), b = findSet(b);
		if(a == b) return;
		if(rank[a] < rank[b]){
			parent[a] = b;
			count[b] += count[a];
		}else{
			parent[b] = a;
			count[a] += count[b];
			if(rank[a] == rank[b]) ++rank[a];
		}
	}
};

struct edge{
	int source, dest, cost;

	edge(): source(0), dest(0), cost(0){}

	edge(int dest, int cost): dest(dest), cost(cost){}

	edge(int source, int dest, int cost): source(source), dest(dest), cost(cost){}

	bool operator==(const edge & b) const{
		return source == b.source && dest == b.dest && cost == b.cost;
	}
	bool operator<(const edge & b) const{
		return cost < b.cost;
	}
	bool operator>(const edge & b) const{
		return cost > b.cost;
	}
};

bool cmp(edge a, edge b)
{
    return a.cost > b.cost;
}

struct graph{
	vector<vector<edge>> adjList;
	vector<vb> adjMatrix;
	vector<vi> costMatrix;
	vector<edge> edges;
	int V = 0;
	bool dir = false;

	graph(int n, bool dir): V(n), dir(dir), adjList(n), edges(n), adjMatrix(n, vb(n)), costMatrix(n, vi(n)){
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				costMatrix[i][j] = (i == j ? 0 : inf);
	}

	void add(int source, int dest, int cost){
		adjList[source].emplace_back(source, dest, cost);
		edges.emplace_back(source, dest, cost);
	}

	vector<edge> kruskal(){
		sort(edges.begin(), edges.end(), cmp);
		vector<edge> MST;
		disjointSet DS(V);
		for(int u = 0; u < V; ++u)
			DS.makeSet(u);
		int i = 0;
		while(i < edges.size() && MST.size() < V - 1){
			edge current = edges[i++];
			int u = current.source, v = current.dest;
			if(DS.findSet(u) != DS.findSet(v)){
				MST.push_back(current);
				DS.unionSet(u, v);
			}
		}
		return MST;
	}
};


////////////////////////////////////////////////*
struct Edge
{
    lli v, c;
    Edge(lli v, lli c): v(v), c(c) {}
};

vector< vector < Edge* > > adj;

void addEdge(lli u, lli v, lli c)
{
    Edge *uv = new Edge(v, c);
    Edge *vu = new Edge(u, c);
    adj[u].push_back(uv);
    adj[v].push_back(vu);
}

const lli logN = 16, INF = 1e18;
vector< bool > visited;
vector< vector< lli > > parent, cost;
vector< lli > depth;


void prep(lli n){
    adj.clear(); adj.resize(n+1); 
    visited.clear(); visited.resize(n+1);
    parent.clear(); parent.assign(n+1, vector<lli> (logN+1));
    cost.clear(); cost.assign(n+1, vector<lli> (logN+1, INF));
    depth.clear(); depth.resize(n+1, 0);
}


void dfs(lli u)
{
    assert(!visited[u]);
    visited[u] = true;
    for(auto E: adj[u])
    {
        lli v = E->v, c = E->c;
        if( !visited[v]  )
        {
            depth[v] = depth[u] + 1;
            cost[v][0] = c;
            parent[v][0] = u;
            for(int i = 1; i<logN; i++)
            {
                parent[v][i] = parent[  parent[v][i-1]  ][i-1];

                cost[v][i] = min( cost[v][i-1], cost[ parent[v][i-1] ][i-1] );
            }
            dfs(v);
        }
    }
}

lli getParent(lli u, lli k) //k-th parent
{
    lli depthK = depth[u] - k;
    for(int i = logN; i>=0; i--)
    {
        if(depth[u] >= depthK + (1<<i))
        {
            u = parent[u][i];
        }
    }
    return u;
}


lli getLCA(lli u, lli v)
{
    if( depth[u] < depth[v]) swap(u, v);
    u = getParent(u, depth[u] - depth[v]);
    assert(depth[u] == depth[v]);
    for(int i = logN; i>=0; i--)
    {
        if(parent[u][i] != parent[v][i])
        {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return (u!=v? parent[u][0]: u);
}

lli query(lli u, lli p)
{
    lli res = INF;
    lli diff = depth[u] - depth[p];
    for(int i = 19; i>=0; i--)
    {
        if(diff & (1<<i))
        {
            res = min(res, cost[u][i]);
            u = parent[u][i];
            diff = depth[u]- depth[p];
        }
    }
    return res;
}

////* ///////////////////////////////////

void solve(lli n, lli m, lli s)
{
    //lli n, m, s; cin>>n>>m>>s;
    graph g(n+1, false);
    forn(i,0,m)
    {
        lli u, v, c; cin>>u>>v>>c;
        g.add(u,v,c);
    }
    vector<edge> tree = g.kruskal();
    //TODO
    prep(n);
    for(auto e: tree)
    {
        addEdge(e.source, e.dest, e.cost);
    }
    /*
    for(int i = 0; i<=n; i++)
    {
        cout<< "Node: " << i  << endl;
        for(auto e: adj[i])
        {
            cout<< e->v << " " << e->c << endl;
        }
        cout<<endl;
    }
    */


    dfs(1);

    while(s--)
    {
        lli u, v; cin>>u>>v;
            if(depth[u] < depth[v]) swap(u,v);
            lli lca = getLCA(u,v);
            lli UL = query(u, lca);
            if( depth[lca] >= depth[v])
            {
                cout<< UL << endl;
            }
            else
            {
                lli VL = query(v, lca);
                cout << min(UL, VL) << endl;
            }
    }
}



int main()
{
    fastIO();
    lli n, m, s;
    while(cin>>n>>m>>s)
    {
        solve(n,m,s);
    }

    return 0;
}