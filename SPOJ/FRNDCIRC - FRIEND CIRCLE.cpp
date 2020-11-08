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
    return dad[u] = root(dad[u]);
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
  // 4
  int getSize(int u) { return size[root(u)]; }

  int numberOfSets() { return n; }
};


map<string, int> mappeo;


int cont = 0;

int mapping(const string &s)
{
    if(!mappeo.count(s))
    {
        mappeo[s] = cont++;
    }
    return mappeo[s];
}


void solve()
{
    int n; cin>>n;
    
    UnionFind U(2*n);
    for(int i = 0; i<n; i++)
    {
        string s, t; cin>>s>>t;
        int u = mapping(s);
        int v = mapping(t);
        U.join(u, v);
        cout << U.getSize(u) << endl;
    }

}



int main () {
	fastIO();
	int t; cin>>t;
    while(t--) solve();

	return 0;
}