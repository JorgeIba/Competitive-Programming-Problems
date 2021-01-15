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

//13
const lli maxN = 1e3+1;
const lli MOD = 1e9;


int nCr[maxN+5][maxN+5];

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
                nCr[i][j] = (nCr[i-1][j-1] + nCr[i-1][j])%MOD;
            }
            //cout << nCr[i][j] << " ";
        }
        //cout << endl;
    }
}


int main () {
	fastIO();
    prec();


    int t; cin>>t;
    while(t--)
    {
        int n, k; cin>>k>>n;
        cout << nCr[n+k-1][k-1] << endl;
    }
    

	return 0;
}