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

int cont = 3;

// 7
struct UnionFind {
  int n;
  vector<int> dad, size, group;

  UnionFind(int N) : n(N), dad(N), size(N, 1), group(N) {
    while (N--)
    {
        dad[N] = N;
        group[N] = cont++;
    } 
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
    group[Rv] = min(group[Rv], group[Ru]);
    size[Rv] += size[Ru];
  }

    bool checkJoin(int u, int v)
    {
        if((alone(u) || alone(v) ) || (getGroup(u) == getGroup(v)) ) return true;
        return false;
    }

    bool checkEat(int u, int v)
    {
        if((alone(u) || alone(v)) || ((getGroup(u)+1)%3 == getGroup(v) ) ) return true;
        return false;   
    }

    bool alone(int u)
    {
        if(group[root(u)] > 2) return true;
        return false;
    }

    void init(int u, int value) {group[root(u)] = value;}


    int getGroup(int u) { return group[root(u)]; }

  bool areConnected(int u, int v) {
    return root(u) == root(v);
  }
  // 4
  int getSize(int u) { return size[root(u)]; }

  int numberOfSets() { return n; }
};

void solve()
{
    int n, k; cin>>n>>k;
    UnionFind U(n+1);
    int ans = 0;
    for(int i = 0; i<k; i++)
    {
        int t, u, v; cin>>t>>u>>v;
        if(u > n || v > n){
            cerr << i << " Mal me pasé \n";
            ans++; continue;
        }
        if(t == 1) // they're same
        {
            if(U.checkJoin(u, v))
            {
                U.join(u, v);
            }
            else
            { 
                cerr << i << " Mal no pueden ser del mismo\n";
                ans++;
            }
        }
        else // u eats v
        {
            if(U.root(u) == U.root(v))
            {
                cerr << i << " Mal son del mismo\n";
                ans++;
                continue;
            }
            if(U.checkEat(u, v))
            {
                if(U.alone(u) && U.alone(v))
                {
                    U.init(u, 0);
                    U.init(v, 1);
                } 
                else
                {
                    if(U.alone(u) && !U.alone(v))   
                    {
                        U.init(u, (U.getGroup(v) + 2)%3 );
                    }
                    else if(!U.alone(u) && U.alone(v))
                    {
                        U.init(v, (U.getGroup(u) + 1)%3);
                    }
                    else
                    {
                        assert(false);
                    }
                    
                }
            }
            else
            {
                cerr << i << " Mal no lo puede comer\n";
                ans++;
            }
        }
        
    }

    for(int i = 1; i<=n; i++) cerr << U.getGroup(i) << " ";
    cerr << endl;
    
    cout << ans << endl;
}



int main () {
	fastIO();
	int t; cin>>t;
    while(t--) solve();
    
	return 0;
}