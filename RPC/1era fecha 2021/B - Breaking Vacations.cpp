#include<bits/stdc++.h>
#define forn(i,n) for(int i = 0; i < n; i++)
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

typedef long double ld;
typedef long long int lli;
typedef vector<int> vi;

const lli INF = 1e9;
const int MAXN = 1e4 + 5;

int  n, k;
int A[MAXN][3];
lli mem[MAXN][105];
bool vis[MAXN][105];

lli dp(int i, int p){
  if(i >= n){
    return p >= k ? 0 : -INF;
  }
  if(vis[i][p]) return mem[i][p];
  vis[i][p] = true;
  return mem[i][p] = max({
    dp(i + 1, min(k, p + A[i][0])),
    dp(i + 1, p) + A[i][1],
    dp(i + 1, p) + A[i][2]
  });
}

int main(){
  fastIO();
  int t;
  cin >> t;
  while(t--){
    cin >> n >> k;
    forn(i, n){
      fill(mem[i], mem[i] + 105, 0);
      fill(vis[i], vis[i] + 105, false);
    }
    //memset(mem, 0, sizeof(mem));
    //memset(vis, 0, sizeof(vis));
    forn(i, n)
      forn(j, 3)
        cin >> A[i][j];
    lli ans = dp(0, 0);
    if(ans <= 0)
      cout << "NO SOLUTION\n";
    else
      cout << ans << endl;
  }
  return 0;
}