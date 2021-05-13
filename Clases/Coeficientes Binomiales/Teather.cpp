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

const int maxN = 30;
lli nCk[maxN+2][maxN+2];
void prec()
{
    nCk[0][0] = 1;
    for(int i = 1; i<=maxN; i++)
    {
        for(int j = 0; j<=maxN; j++)
        {
            if(j > i) break;
            else if(j == 0 || j == i) nCk[i][j] = 1;
            else{
                nCk[i][j] = nCk[i-1][j] + nCk[i-1][j-1];
            }
        }
    }
}



int main () {
	//fastIO();
    prec();
    lli n, m, t; cin>>n>>m>>t;

    lli ans = 0;
    for(lli chicos = 4; chicos <= n; chicos++)
    {
        lli chicas = t - chicos; // chicas decreciente
        if(chicas < 1) break;
        if(chicas > m) continue;

        ans += nCk[n][chicos] * nCk[m][chicas];
    }
    cout << ans << endl;
	return 0;
}