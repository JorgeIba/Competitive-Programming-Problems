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
	bool operator<(const edge & b) const{
		return cost < b.cost;
	}
};

struct graph{
	vector<edge> edges;
	int V = 0;
	bool dir = false;

	graph(int n, bool dir): V(n) {

	}

	void add(int source, int dest, int cost){
		edges.emplace_back(source, dest, cost);
	}

	vector<edge> kruskal(){
		sort(all(edges));
		vector<edge> MST;
		disjointSet DS(V);
		for(int u = 0; u < V; ++u)
			DS.makeSet(u);
		int i = 0;
		while(i < SZ(edges) && SZ(MST) < V - 1){
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


vector< vector<lli> > dist;
vector< vector<lli> > mat;
vector< vector<lli> > adjList;

int n; 

void bfs_dist(int start)
{
    queue<int> q;

    q.push(start);

    while(!q.empty())
    {
        int u = q.front(); q.pop();

        for(auto v: adjList[u])
        {
            if(v != u)
            {
                q.push(v);
                dist[start][v] = dist[start][u] + mat[u][v];
            }
        }
    }
    return;
}


int main () {
	fastIO();
    cin>>n;

    graph G(n, false);

    vector< vector<lli> > adjMat(n, vector<lli>(n));

    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            lli c; cin>>c;
            if(i == j && c > 0)
            {
                cout << "NO\n";
                return 0;
            }
            if(c == 0) continue;
            G.add(i, j, c);
            adjMat[i][j] = c;
        }
    }

    mat.assign(n, vector<lli>(n));
    adjList.resize(n);

    auto edges = G.kruskal();
    for(auto e: edges)
    {
        int s = e.source, d = e.dest, c = e.cost;
        adjList[s].push_back(d);
        adjList[d].push_back(s);
        mat[s][d] = c;
        mat[d][s] = c;
    }


    dist.assign(n, vector<lli>(n));
    for(int i = 0; i<n; i++)
    {
        bfs_dist(i);
    }


    /*
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            cout << dist[i][j] << " ";
        }
        cout << endl;
    }
    */
    
   
    bool ans = true;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            if(i != j && dist[i][j] == 0) ans = false;
        }
    }
    
    if(dist == adjMat && ans)
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
    }
    


	return 0;
}