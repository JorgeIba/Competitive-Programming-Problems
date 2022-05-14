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


// 7
struct UnionFind {
  int n;
  vector<int> dad, size;

  UnionFind(int N) : n(N), dad(N), size(N, 1) {
    while (N--) dad[N] = N;
  }
  // 4
  // O(lg*(N))
  int root(int u) {
    if (dad[u] == u) return u;
    return root(dad[u]);
  }
  // 8
  // O(1)
  void join(int u, int v) {
    int Ru = root(u), Rv = root(v);
    if (Ru == Rv) return;
    if (size[Ru] > size[Rv]) swap(Ru, Rv);
    --n, dad[Ru] = Rv;
    size[Rv] += size[Ru];
  }
  // 4
  // O(lg*(N))
  bool areConnected(int u, int v) {
    return root(u) == root(v);
  }

  int getSize(int u) { return size[root(u)]; }

  int numberOfSets() { return n; }
};



struct edge{
    int idx, u, v;
    edge() {}
    edge(int idx, int u, int v): idx(idx), u(u), v(v) {}
};



map<int,int> original_to_map;
map<int,int> map_to_original;

int cnt = 0;
int map_nodo(int idx)
{
    if(!original_to_map.count(idx)){
        original_to_map[idx] = cnt;
        map_to_original[cnt++] = idx ;
    }
    return original_to_map[idx];
}


void solve()
{
    cnt = 0;
    original_to_map.clear();
    map_to_original.clear();

    lli n; cin>>n;
    vector<edge> edges;
    
    for(int i = 1; i <= n; i++)
    {
        lli u, v; cin>>u>>v;
        edges.push_back(edge(i, map_nodo(u) , map_nodo(v)));
    }


    lli m = SZ(map_to_original);
    vector<vector<pair<lli,lli>>> adjList( m );

    UnionFind *UF = new UnionFind(m);

    vector<edge> available;
    for(auto e: edges) {
        if(!UF->areConnected(e.u, e.v)){
            UF->join(e.u, e.v);
            adjList[e.u].push_back({e.idx, e.v});
            adjList[e.v].push_back({e.idx, e.u});
        } else {
            available.push_back(e);
        }
    }


    map< lli, vector<edge> > available_in_roots;
    for(auto e: available) {
        lli root_u = UF->root(e.u);
        available_in_roots[root_u].push_back(e);
    }

    for(int i = 0; i < m; i++)
    {
        int root_u = UF->root(i);
        if(root_u != i && SZ(adjList[i]) == 1){
            available_in_roots[root_u].push_back( edge( adjList[i][0].first, adjList[i][0].second, i  )   );
        }
    }


    vector< pair<lli, vector<edge>> > available_total;
    for(auto u: available_in_roots) available_total.push_back({u.first, u.second});
    

    int roots_n = UF->numberOfSets() - 1;
    cout << roots_n << endl;

    for(int i = 1; i <= roots_n; i++){
        int idx = available_total[i].second[0].idx;
        edge need = available_total[i].second[0];

        cout << idx << " " << map_to_original[need.v] << " " << map_to_original[available_total[0].first] << endl;
    }


}


int main () {
	fastIO();

    int t; cin>>t;

    while(t--) solve();


	return 0;
}