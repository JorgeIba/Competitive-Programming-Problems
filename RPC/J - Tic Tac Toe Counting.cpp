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

map<string, pii> vis;

pii winner(string &s) {
  // horizontal
  forn(i, 3) {
    if (s[3 * i] == '.')
      continue;
    if (s[3 * i] == s[3 * i + 1] && s[3 * i] == s[3 * i + 2])
      return {s[3 * i] == 'X', s[3 * i] == 'O'};
  }
  // vertical
  forn(i, 3) {
    if (s[i] == '.')
      continue;
    if (s[i] == s[3 + i] && s[i] == s[6 + i])
      return {s[i] == 'X', s[i] == 'O'};
  }
  /*
   0 . . . 4 . . . 8
   */
  if (s[0] != '.') {
    if (s[0] == s[4] && s[0] == s[8])
      return {s[0] == 'X', s[0] == 'O'};
  }
  if (s[2] != '.') {
    if (s[2] == s[4] && s[2] == s[6])
      return {s[2] == 'X', s[2] == 'O'};
  }
  return {0, 0};
}

pii dfs(string &curr, bool o) {
  if (vis.count(curr))
    return vis[curr];
  auto [x, y] = winner(curr);
  if (x || y)
    return vis[curr] = {x, y};
  forn(i, 9) {
    if (curr[i] == '.') {
      if (o)
        curr[i] = 'O';
      else
        curr[i] = 'X';
      auto [u, v] = dfs(curr, o ^ 1);
      x += u, y += v;
      curr[i] = '.';
    }
  }
  vis[curr] = {x, y};
  return {x, y};
}

int main() {
  fastIO();
  string init = ".........";
  dfs(init, false);
  int n;
  cin >> n;
  forn(i, n) {
    string s;
    cin >> s;
    if (vis.count(s))
      cout << vis[s].first << ' ' << vis[s].second << endl;
    else
      cout << -1 << ' ' << -1 << endl;
  }
  return 0;
}
