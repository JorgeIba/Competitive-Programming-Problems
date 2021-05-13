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

const lli maxN = 20;
lli nCr[maxN+5][maxN+5];

void prec()
{
    nCr[0][0] = 1;
    for(int i = 1; i<maxN; i++)
    {
        for(int j = 0; j<=i; j++)
        {
            if(j==0 || j == i) nCr[i][j] = 1;
            else
            {
                nCr[i][j] = (nCr[i-1][j-1] + nCr[i-1][j]);
            }
            //cout << nCr[i][j] << " ";
        }
        //cout << endl;
    }
}

int main () {
	fastIO();
    prec();
    lli t; cin>>t;
    while(t--)
    {
        lli a, b, c, n, k; cin>>a>>b>>c>>n>>k;
        ld ans  = 0;
        lli total = a+b+c;
        for(int i = k; i<=a; i++)
        {
            if(total - a >= 0 && n-i >= 0)
                ans += (ld)(nCr[a][i])*(nCr[total-a][n-i])/(nCr[total][n]);
        }
        cout << fixed << setprecision(4) << ans << endl;
    }
    

    
	return 0;
}