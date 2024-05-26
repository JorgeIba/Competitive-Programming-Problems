#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;


const int maxn = 1e6 + 10;
int dis[maxn];


int main() {
  memset(dis, -1, sizeof(dis));
  int f, s, g, u, d;
  cin >> f >> s >> g >> u >> d;
  queue<int> q;
  q.push(s);
  dis[s] = 0;
  while(!q.empty()) {
    int cu = q.front(); q.pop();
    if(cu + u <= f) {
      if(dis[cu + u] == -1) {
        q.push(cu + u);
        dis[cu + u] = dis[cu] + 1;
      }
    }
    if(cu - d >= 1) {
      if(dis[cu - d] == -1) {
        q.push(cu - d);
        dis[cu - d] = dis[cu] + 1;
      }
    }
  }
  if(dis[g] == -1) {
    cout << "use the stairs\n";
  }
  else cout << dis[g] << '\n';
  return 0;
}
