#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define point pair<lli,lli>
#define x first
#define y second

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

struct UnionFind {
  int n;
  vector<int> dad, size;

  UnionFind(int N) : n(N), dad(N), size(N, 1){
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
};


void solve()
{
    int n, m; cin>>n>>m;
    vector<int> xs(n+1), ys(n+1);

    UnionFind U(m+1);
    int ans = 0;
    for(int i = 1; i<=m; i++)
    {
        int x, y; cin>>x>>y;
        if(x == y) continue;
        ans++;
        xs[x] = i, ys[y] = i;

        if(ys[x])
            U.join(ys[x], i);
        
        if(xs[y])
        {
            if(U.areConnected(xs[y],i)) ans++;
            else U.join(xs[y], i);
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