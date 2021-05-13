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

vector< pair<lli,lli>  > adjList;
vector<lli> chueco;

const int maxN = 1e5+10;

lli dp[maxN][2][2];

lli nand(lli u1, lli u2, lli t)
{
    if(t != -1) return t;
    return !(u1 & u2);
}

const lli MOD = 1e9+7;

void dfs(lli idx)
{
    if(idx == 0) return;
    lli u = adjList[idx].first, v = adjList[idx].second;
    dfs(u);
    dfs(v);

    for(int i = 0; i<=1; i++)
    {
        for(int j = 0; j<=1; j++)
        {
            for(int q = 0; q<=1; q++)
            {
                for(int k = 0; k<=1; k++) // dp[u][x][y] cuantas formas el u esperaba el x y le llegó el y
                {
                    lli exp = nand(i, q, -1), come = nand(j, k, chueco[idx]);
                    dp[idx][exp][come] += dp[u][i][j]*dp[v][q][k] % MOD;
                    if(dp[idx][exp][come] >= MOD)  dp[idx][exp][come] -= MOD;
                }
            }
        }
    }    
    return;
}


int main () {
	//fastIO();
    lli n; cin>>n;
    adjList.resize(n+1);
    chueco.resize(n+1);
    for(int i = 1; i<=n; i++)
    {
        lli u, v, y; cin>>u>>v>>y;
        adjList[i].first = u;
        adjList[i].second = v;
        
        chueco[i] = y;
    }

    dp[0][0][0] = 1;
    dp[0][1][1] = 1;

    dfs(1);

    cout << (dp[1][1][0] + dp[1][0][1])%MOD << endl;

	return 0;
}