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

vector<lli> parent;
vector< vector<lli> > adjList;

vector<lli> minLeaf;

const lli MOD = 998244353;
const lli INF = (lli)1e18;

lli dfs(int u) {
  minLeaf[u] = 1;
  lli minChild = INF;
  for(int v : adjList[u]) {
    if(v == parent[u]) continue;
      minChild = min(minChild, dfs(v));
  }
  if(minChild == INF) return 1;
  minLeaf[u] += minChild;
  return minLeaf[u];
}

const int maxN = 2e5 + 100;
lli sum = 0;
lli dp[maxN];
lli binPow(lli a, lli e, lli mod){
  lli ans = 1;
  while(e) {
    if(e&1) ans = ans*a % mod;
    a = a*a%mod;
    e >>= 1;
  }
  return ans;
}
void f(lli u)
{
  lli best = 0;
  if(u == 1)
  {
    best = minLeaf[u];
  }
  else
  {
    best = min( minLeaf[u], dp[parent[u]] +1);
  }

  dp[u] = best;

  for(auto v: adjList[u])
    f(v);
  return;
}


int main () {
	fastIO();
  lli n; cin>>n;
  parent.resize(n+1);
  adjList.resize(n+1);
  minLeaf.resize(n+1);
  
  for(int i = 2; i<=n; i++)
  {
    cin>>parent[i];
    adjList[parent[i]].push_back(i);
  }
  lli sum = 0;
  dfs(1);
  f(1);
  for(int i = 1; i <= n; i++) {
    sum = (sum + dp[i]) % MOD;
  }

  cout << sum * binPow(n, MOD-2, MOD) % MOD << endl;
  
	return 0;
}

