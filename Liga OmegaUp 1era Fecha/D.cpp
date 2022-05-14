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


lli n, m;
vector< vector<lli> > matriz;
vector< vector<bool> > visited;


bool is_inside(lli i, lli j)
{
    if( i < 0 || i >= n || j < 0 || j >= m  ) return false;
    return true;
}


vector< pair<lli,lli> > dirs = {            {-1, 0}, 
                                  {0, -1} ,          {0, 1},
                                             {1, 0}
                                };


lli dfs(lli i, lli j)
{
    if((!is_inside(i, j)) || (matriz[i][j] == 0) || (visited[i][j] == true)) return 0;


    visited[i][j] = true;

    lli ans = 1;
    for(auto dir: dirs)
    {
        lli di = dir.first, dj = dir.second;
        ans += dfs(i + di, j + dj);
    }
    return ans;
}


lli solve()
{
    cin>>n>>m;

    matriz.assign(n, vector<lli>(m, 0));
    visited.assign(n, vector<bool>(m, false));


    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            cin >> matriz[i][j];
        }
    }

    lli ans = 0;

    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(visited[i][j]) continue;


            lli sz = dfs(i, j);
            ans = max(ans, sz);
        }
    }

    return ans;
}



int main () {
	fastIO();

    lli t; cin>>t;

    for(int i = 1; i<=t; i++)
    {
        lli ans = solve();
        cout << "Case #" << i << ": " << ans << endl;
    }


	return 0;
}

