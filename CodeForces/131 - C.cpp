#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


//15
const lli maxN = 30;
lli nCr[maxN+5][maxN+5];
void prec()
{
    nCr[0][0] = 1;
    for(int i = 1; i<=maxN; i++)
    {
        for(int j = 0; j<=i; j++)
        {
            if(j==0 || j == i) nCr[i][j] = 1;
            else
            {
                nCr[i][j] = (nCr[i-1][j-1] + nCr[i-1][j]);
            }
        }
    }
}


int main () {
	//fastIO();
    prec();
    lli n, m, t; cin>>n>>m>>t;

    lli ans = 0;
    for(int i = 4; i<=n; i++)
    {
        if( t-i < 1) break;
        if( m < t-i ) continue;
        
        ans += nCr[n][i] * nCr[m][t-i];
    }
    cout << ans << endl;

	return 0;
}