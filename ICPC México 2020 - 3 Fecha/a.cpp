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

vector<lli> energy; //energía de cada wey
vector<lli> difficult; // dificultad de cada uno
vector<lli> score; // puntaje que da cada wey

int t, n; // t -> numero de weyes, n-> numero de problemas

int mem[103][(1<<10)+3][103];

const int inf = 1e9;
int dp(int p, int mask, int e){
  if(e < 0) return -inf;
  if(p == n)
    return 0;
  int& ans = mem[p][mask][e];
  if(ans != -1) return ans;
  ans = 0;
  int op1 = dp(p+1, mask, e);
  int op2 = dp(p+1, mask, e - difficult[p]) + score[p];
  int op3 = -inf;
  //11001
  for(int i = 0; i < t; i++){
    if(!((1<<i)&mask))
      op3 = max(op3, dp(p,mask | (1<<i), energy[i]));
  }
  return ans = max({op1,op2,op3});
}

int main () {
	//fastIO();
  memset(mem, -1, sizeof(mem));

  cin>>t>>n;
  energy.resize(t);
  difficult.resize(n);
  score.resize(n);
  for(auto &x: energy) cin>>x;
  for(auto &x: difficult) cin>>x;
  for(auto &x: score) cin>>x;

  int ans = 0;
  for(int i = 0; i<t; i++)
  {
    ans = max(ans, dp(0, (1<<i), energy[i]) );
  }
  cout << ans << endl;

  return 0;
}