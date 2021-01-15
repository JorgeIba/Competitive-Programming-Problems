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
  bool areConnected(int u, int v) {
    return root(u) == root(v);
  }
  int getSize(int u) { return size[root(u)]; }

  int numberOfSets() { return n; }

};


struct Edge{
    lli u, v, cost;
    Edge() {}
    Edge(lli u, lli v, lli cost): u(u), v(v), cost(cost) {}
};

lli n, m, k; 

bool compare1(Edge a, Edge b)
{
    return a.cost > b.cost;
}

bool compare2(Edge a, Edge b)
{
    return a.cost < b.cost;
}

bool compare3(Edge a, Edge b)
{
    return abs(k-a.cost) < abs(k-b.cost);
}


void solve()
{
    cin>>n>>m>>k;
    vector< Edge > adj(m);

    vector< Edge > menor, mayor;

    UnionFind F(n);

    for(int i = 0; i<m; i++)
    {
        cin>>adj[i].u>>adj[i].v>>adj[i].cost;
        adj[i].u--, adj[i].v--;
        if(adj[i].cost <= k) menor.push_back(adj[i]);
        else mayor.push_back(adj[i]);
    }

    sort(all(menor), compare1);
    sort(all(mayor), compare2);
    sort(all(adj), compare3);

    lli ans = 0;
    for(auto E: menor)
    {
        if(!F.areConnected(E.u, E.v))
        {
            F.join(E.u, E.v);
        }
    }
    if(F.numberOfSets() == 1) //Se puede poner puros menores
    {
        //UnionFind U(n);
        //U.join(adj[0].u, adj[0]. v);
        ans = abs(k-adj[0].cost);
    }
    else //Menores y uno que otro mayor
    {
        for(auto E: mayor)
        {
            if(!F.areConnected(E.u, E.v))
            {
                ans += (E.cost - k);
                F.join(E.u, E.v);
            }
        }
    }
    cout << ans << endl;
    
}


int main () {
	fastIO();
    int t; cin>>t;
    while(t--) solve();
    
	return 0;
}