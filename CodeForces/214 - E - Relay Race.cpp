#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
 
using namespace std;

vector< vector< lli > > mat;
lli n;
int dp[2*305][305][305];
const int INF = 1e9;

int fun(lli diag, lli x1, lli x2)
{
    int y1 = diag - x1 + 1, y2 = diag - x2 + 1;
    if(y1 > n || y2 > n || x1 > n || x2 > n) return -1000000LL;
    if(diag == 2*n - 1) return mat[n][n];

    int curr = mat[x1][y1];
    if(x1 != x2)
        curr += mat[x2][y2];

    int &res = dp[diag][x1][x2];
    if(res != -INF) return res;


    for(int d1=0; d1<=1; d1++)
    {
        for(int d2 = 0; d2<=1; d2++)
        {
            res = max(res, curr + fun(diag+1, x1 + d1, x2 + d2));
        }
    }
    return res;
}

int main () {
	fastIO();
    forn(i,2*304) forn(j, 304) forn(q, 304) dp[i][j][q] = -INF;
    cin>>n;
    mat.assign(n+1, vector<lli>(n+1));
    for(int i = 1; i<=n; i++) for(int j = 1; j<=n; j++) cin>>mat[i][j];

    cout << fun(1, 1, 1) << endl;

	return 0;
}