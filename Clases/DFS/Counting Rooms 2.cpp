#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

pair<int,int> deltas[4] = {
    {-1, 0}, // Arrriba
{0, -1},   {0, 1}, // Izquierda y derecha
    {1, 0}   // Abajo
};

int main () {


    int n, m; cin>>n>>m;
    vector<string> mat(n);

    for(auto &s: mat) cin>>s;

    auto isInside = [&](int x, int y){
        return (0 <= x && x < n && 0 <= y && y < m);
    };

    vector< vector<bool> > visited(n, vector<bool>(m));
    auto dfs = [&](const auto &dfs, int x, int y) -> void {
        visited[x][y] = true;
        for(auto [dx, dy]: deltas){
            if(isInside(x+dx, y+dy) && mat[x+dx][y+dy] == '.' && !visited[x+dx][y+dy]){
                dfs(dfs, x+dx, y+dy);
            }
        }
    };

    int ans = 0;
    forn(i, n){
        forn(j, m){
            if(mat[i][j] == '#' || visited[i][j]) continue;

            ans++;
            dfs(dfs, i, j);
        }
    }

    cout << ans << endl;

	return 0;
}
