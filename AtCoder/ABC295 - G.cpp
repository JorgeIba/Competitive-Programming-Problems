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

struct UnionFind {
  int n;
  vector<int> dad, size;
  vector<int> mini;

  UnionFind(int N) : n(N), dad(N), size(N, 1), mini(N) {
    for(int i = 0; i < N; i++) mini[i] = i;
    for(int i = 0; i < N; i++) dad[i]  = i;
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
    mini[Rv] = min(mini[Rv], mini[Ru]);
  }

  bool areConnected(int u, int v) {
    return root(u) == root(v);
  }
  
  int getSize(int u) { return size[root(u)]; }
  int getMini(int u) { return mini[root(u)]; }

  int numberOfSets() { return n; }
};


void main_(){
	int n; cin>>n;

    vector< vector<int> > adjList(n+1);
    vector< int > parent(n+1);

    for(int i = 1; i <= n-1; i++){
        int p; cin>>p;
        adjList[p].push_back(i + 1);
        parent[i+1] = p;
    }


    UnionFind *UF = new UnionFind(n+1);

    int q; cin>>q;
    while(q--) {
        int t; cin>>t;
        if(t == 1) {
            int u, v; cin>>u>>v;

            int curr = u;
            while(!UF->areConnected(u, v)) {
                UF->join(u, curr);
                curr = parent[ UF->getMini(u) ];
            }

        } else {
            int u; cin>>u;

            cout << UF->getMini(u) << endl;
        }
    }
}


int main () {
	fastIO();
	
	int t = 1;
	// cin>>t;
	
	while(t--) main_();


	return 0;
}

