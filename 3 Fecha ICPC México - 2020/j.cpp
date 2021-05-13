#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define pb push_back

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

const int MAXN = 1005;

int N,M,K; //N -> nodos, M -> aristas, K -> cost
int O,T; 
int entregas[MAXN], especial[MAXN];
int V[MAXN];
vector< vector<lli> > adjList; //adjList -> lista de adyacencia
vector< vector<lli> > costMat; //costo -> costo minimo de u a v

const int INF = 1e9;

VLL bfs(int u)
{
    queue<lli> q;
    vector<lli> dist(N, INF);
    
    dist[u] = 0;
    q.push(u);

    while(!q.empty())
    {
      int u = q.front(); q.pop();
      for(auto v: adjList[u])
      {
        if(v != u && dist[v] == INF)
        {
          q.push(v);
          dist[v] = dist[u]+K;
        }
      }
    }
  return dist;
}



int mem[1005][10005];

int dp(int i, int tiempo){
  if(tiempo < 0) return -INF;
  if(i == O) return V[i];
  if(mem[i][tiempo] != -1) return mem[i][tiempo];
  mem[i][tiempo] = -INF;
  return mem[i][tiempo] = max(dp(i+1, tiempo-costMat[entregas[i]][entregas[i+1]]),dp(i+1, tiempo - costMat[entregas[i]][especial[i]] - costMat[especial[i]][entregas[i+1]])+V[i]);
}

int main () {
	//fastIO();
  memset(mem,-1,sizeof(mem));
  cin >> N >> M >> K;

  adjList.resize(N);
  costMat.resize(N);
  
  forn(i,M){
    int u,v;
    cin >> u >> v;
    u--; v--;
    adjList[u].pb(v);
    adjList[v].pb(u);
  }
  cin >> O >> T;
  forn(i,O){
    cin >> entregas[i];
    entregas[i]--;
  }
  forn(i,O){
    cin >> especial[i] >> V[i];
    especial[i]--;
  }
  forn(i,N){
    costMat[i] = bfs(i);
  }
  lli ans = dp(0,T-costMat[0][entregas[0]]);
  if(ans < 0) 
  {
    cout << "Impossible\n";
  }
  else
  {
    cout << ans << endl;
  }
	return 0;
}