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
int n;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

bool inside(int x, int y) { return x >= 0 && x < n && y >= 0 && y < n; }

int dfs(int i, int j, int curr, vector<vector<int>> &mat) {
  mat[i][j] = -1;
  int sz = 1;
  forn(k, 4) {
    int x = i + dx[k];
    int y = j + dy[k];
    if (inside(x, y) && mat[x][y] == curr)
      sz += dfs(x, y, curr, mat);
  }
  return sz;
}

lli gauss(lli n) { return n * (n + 1) / 2; }

int main() {
  fastIO();
  cin >> n;
  vector<vector<int>> sizes(n, vi(n));
  vector<vector<int>> animals(n, vi(n));
  forn(i, n) forn(j, n) {
    char c;
    int x;
    cin >> c >> x;
    c -= 'A';
    x--;
    sizes[i][j] = x;
    animals[i][j] = c;
  }
  vector<int> max_animals(26, 0);
  vector<int> max_szs(n, 0);
  forn(i, n) forn(j, n) {
    if (animals[i][j] != -1) {
      int curr = animals[i][j];
      max_animals[curr] = max(max_animals[curr], dfs(i, j, curr, animals));
    }
    if (sizes[i][j] != -1) {
      int curr = sizes[i][j];
      max_szs[curr] = max(max_szs[curr], dfs(i, j, curr, sizes));
    }
  }
  lli ans_a = 0;
  lli ans_b = 0;
  for (int x : max_animals)
    ans_a += gauss(x - 1);
  for (int x : max_szs)
    ans_b += gauss(x - 1);
  cout << ans_a << ' ' << ans_b << endl;
  return 0;
}
