#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,n) for(int i = a; i <= n; i++)
#define all(v) v.begin(), v.end()
#define se second
#define fi first
#define pb push_back
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
 
using namespace std; 

typedef pair<lli, lli> plli;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<lli>> vvlli;
typedef vector<lli> vlli;
typedef vector<pii> vpii;

int n, m, maxDis;
char mat[1005][1005];
bool vis[2000005];
char let[] = {'D', 'L', 'R', 'U'};
pii movimientos[] = {{1,0},{0,-1},{0,1},{-1,0}};
vector<string> ans;
int getCoord(int x, int y){
  return n*x + y; 
}
bool inside(int x, int y){
  return (x >= 0 && x < n && y >= 0 && y < m);
}
void dfs(int x, int y, vi& dis, string& act, int actDis){
  int u = getCoord(x,y);
  if(mat[x][y] == '#')
    return;
  if(dis[u] == maxDis && actDis == maxDis){
    ans.pb(act);
    //cout << "X: " << x << ' ' << "Y: " << y << '\n';
    return;
  }
  for(int i = 0; i < 4; i++){
    auto mov = movimientos[i];
    if(inside(x+mov.fi, y+mov.se)){
      int v = getCoord(x+mov.fi, y+mov.se);
      if(!vis[v]){
        act.pb(let[i]);
        dfs(x+mov.fi, y+mov.se, dis, act,actDis+1);
        act.pop_back();
      }
    }
  }
}

void bfs(int x, int y){
  vi dis(n*m, -1);
  queue<pair<int,int>> q;
  vector<pair<int,char> > parent(n*m);
  q.push({x,y});
  dis[getCoord(x, y)] = 0;
  parent[getCoord(x,y)] = {-1, '0'};
  while(!q.empty()){
    auto act = q.front();
   // cout << "Actual: " << act.fi << ' ' << act.se << '\n'; 
    q.pop();
  //  cout << "Mete: ";
    for(int i = 0; i < 4; i++){
      auto mov = movimientos[i];
      if(inside(act.fi+mov.fi, act.se+mov.se) && mat[act.fi+mov.fi][act.se+mov.se] == '.'){
        if(dis[getCoord(act.fi+mov.fi, act.se+mov.se)] == -1){
          q.push({act.fi+mov.fi, act.se+mov.se});
          dis[getCoord(act.fi+mov.fi, act.se+mov.se)] = dis[getCoord(act.fi, act.se)] + 1;
	  parent[getCoord(act.fi+mov.fi, act.se + mov.se)] = {getCoord(act.fi,act.se),let[i]};
//	  cout << "{" << act.fi + mov.fi << ", " << act.se + mov.se << "} ";
        }
      }
    }
   // cout << '\n';
  }
  maxDis = -1;
  for(int x : dis) maxDis = max(maxDis, x);
  forn(i,SZ(dis)){
	  if(dis[i] == maxDis){
		 int u = i;
		 string recAns;
		 while(parent[u].fi != -1){
			 recAns += parent[u].se;
			 u = parent[u].fi;
		 }
		 reverse(all(recAns));
		 ans.pb(recAns);
	  }
  }
  sort(all(ans));
}
int main(){
  int t;
  cin >> t;
  forn(k,t){
    ans.clear();
    memset(vis, 0, sizeof(vis));
    cin >> m >> n;
    int x, y;
    forn(i,n)
      forn(j,m){
        cin >> mat[i][j];
        if(mat[i][j]=='@'){
          x = i;
          y = j;
	  //cout << "X: " << x << ' ' << "Y: " <<  y << '\n';
        }
      }
    bfs(x,y);
    cout << "Case " << k+1 << ":\n";
    if(maxDis > 0){
    	cout << ans.size() << ' ' << maxDis << '\n';
    	for(string p : ans) cout << p << '\n';
    }
    else cout << "0 0\n";
  }
  return 0;
}
