#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

const int MAXN = 3e5 + 1000;

vector<int> adjList[MAXN];
int weights[MAXN];

struct UnionFind {
    int n;
    vector<int> dad, size;

    UnionFind(int N) : n(N), dad(N), size(N, 1) {
        while (N--) dad[N] = N;
    }
  
    int root(int u) {
        if (dad[u] == u) return u;
        return dad[u] = root(dad[u]);
    }
  
    void join(int u, int v) {
        int Ru = root(u), Rv = root(v);
        if (Ru == Rv) return;
        if (size[Ru] > size[Rv]) swap(Ru, Rv);
        --n, dad[Ru] = Rv;
        size[Rv] += size[Ru];
    }
};

int main () {
	fastIO();

    int n, m, x; cin>>n>>m>>x;

    forn(i, n) cin>>weights[i];

    map< pair<int,int>, int > edge_to_idx;
    forn(i, m){
        int u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        edge_to_idx[{min(u, v), max(u, v)}] = i+1;
    }


    lli sum = 0;
    forn(i, n)
        sum += weights[i];

    lli total_edges = n-1;
    if(sum < total_edges*x) {
        cout << 0 << endl;
        return 0;
    }

    auto cmp = [](auto a, auto b) { return a > b; };
    multiset<pair<lli,int>, decltype(cmp)> pool(cmp);

    forn(i, n){
        pool.insert({weights[i], i});
    }

    vector< int > parent(n);    
    vector<pair<int,int>> edges;
    UnionFind UF(n);
    vector<int> total_weights(n);
    forn(i, n) total_weights[i] = weights[i];

    while(!pool.empty()){
        auto itr = pool.begin();
        auto [fuel_u, u] = *itr; pool.erase(itr);

        assert(fuel_u >= x);

        edges.push_back({u, parent[u]});

        sort(all(adjList[u]), [&](auto a, auto b){
            return total_weights[ UF.root(a) ] > total_weights[ UF.root(b) ];
        });

        for(auto v: adjList[u]){
            auto Rv = UF.root(v);
            if(v == UF.root(u)) continue;

            lli total_fuel = total_weights[ UF.root(u) ] + total_weights[ UF.root(v) ];

            parent[v] = u;
            UF.join(u, Rv);
            pool.insert({  , v});
        }
    }

    // debugg(start);
    cout << "YES" << endl;
    for(auto [u, v]: edges){
        cout << edge_to_idx[{min(u,v), max(u, v)}] << endl;
        // cout << u+1 << " -> " << v+1 << endl;
    }


	return 0;
}
