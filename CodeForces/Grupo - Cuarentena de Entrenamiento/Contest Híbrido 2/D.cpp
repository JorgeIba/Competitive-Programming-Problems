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



const lli SZ = 26;

// lli getMask(string &s) {
//     lli mask = 0;
//     for(auto c: s) {
//         lli idx = c-'a';
//         mask = mask | (1LL << idx);
//     }
//     return mask;
// }



// lli target;
// vector<lli> masks;
// const lli INF = 1e9;

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




int main () {
	//fastIO();
    lli n; cin>>n;

    vector<string> passwords(n);
    for(auto &x: passwords) cin>>x;


    UnionFind *UF = new UnionFind(SZ + n+1);



    for(int i = 0; i < n; i++) {
        auto pass = passwords[i];
        for(auto c: pass) {
            UF->join(c-'a', SZ + i+1);
        }
    }


    set<lli> seen;
    for(int i = 0; i < SZ+n+1; i++) {
        seen.insert( UF->root(i) );
    }

    lli ans = 0;
    for(auto x: seen) {
        ans += (UF->getSize(x) > 1);
    }
    cout << ans << endl;


	return 0;
}

