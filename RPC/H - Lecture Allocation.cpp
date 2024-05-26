#include <bits/stdc++.h>
#define lli long long int
#define ld long double
#define forn(i, n) for (int i = 0; i < n; i++)
#define forr(i, a, n) for (int i = a; i <= n; i++)
#define fi first
#define se second
#define pb push_back
#define all(v) v.begin(), v.end()
#define SZ(v) (int)v.size()
#define endl '\n'
#define fastIO()                                                               \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);                                                                  \
  cout.tie(0);

using namespace std;

typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<lli> vlli;
int L, T;

const lli inf = 1e17;
const int MAXN = 5005;
lli mem[MAXN][MAXN];
lli cost[MAXN][4];

lli dp(int teach, int prob) {
  if (prob >= L)
    return 0;
  if (teach >= T)
    return inf;
  lli &a = mem[teach][prob];
  if (a != -1)
    return a;
  a = inf;
  forn(i, 4) { a = min(a, dp(teach + 1, prob + i) + cost[teach][i]); }
  return a;
}

int main() {
  fastIO();
  cin >> L >> T;
  forn(i, T) { cin >> cost[i][1] >> cost[i][2] >> cost[i][3]; }
  memset(mem, -1, sizeof(mem));
  lli ans = dp(0, 0);
  cout << ans << endl;
  return 0;
}
