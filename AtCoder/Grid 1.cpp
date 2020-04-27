#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli MOD = 1e9 + 7;

vector< string > matrix;
lli n, m;
vector< vector<lli> > dp;

lli f(lli i, lli j)
{
    if(i>=n || j>=m) return 0;
    if(i==n-1 && j == m-1) return 1;
    if(matrix[i][j] == '#' ) return 0;
    if(dp[i][j] != -1) return dp[i][j];

    return dp[i][j] = (f(i+1, j) + f(i, j+1))%MOD;
}


int main()
{
    fastIO();
    cin>>n>>m;
    matrix.resize(n);
    dp.assign(n, vector<lli> (m,-1));
    forn(i,0,n)
    {
        cin>>matrix[i];
    }
    cout<<f(0,0)<<endl;
    return 0;
}