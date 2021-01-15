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

ld dp[5000][20];
lli rating[5000];

int main () {
	fastIO();
    lli n; cin>>n;
    for(int i = 1; i<=n; i++) cin>>rating[i];
    sort(rating+2, rating+n+1);

    //for(int i = 1; i<=n; i++) cout << rating[i] << " ";
    lli levels, N;
    for(levels = 0, N=1; N<n; levels++, N<<=1);

    //cout << levels << " " << N << " " << N-n << endl;
    vector<lli> aux(N);
    for(int i = 0, j = 1, howMuch = N-n; i<N; i++)
    {
        if(i&1 && howMuch)
        {
            aux[i] = 0; howMuch--;
        } 
        else aux[i] = rating[j++];
        //cout << i << " " << j << endl;
    }
    
    

    //for(auto x: aux) cout << x << " ";

    for(int i = 1; i<=N; i++) dp[i][0] = 1;

    for(int k = 1; k<=levels; k++)
    {
        for(int i = 1; i<=N; i++)   
        {
            if(aux[i-1] < 1) continue;
            lli sz_bloque = (1<<k), inicio_bloque = (i-1)/sz_bloque, anterior = (1LL<<(k-1));
            lli limitL, limitR;

            if(i <= inicio_bloque*sz_bloque + anterior)
            {
                limitL = ((sz_bloque)*inicio_bloque) + 1 + anterior;
                limitR = sz_bloque*(inicio_bloque+1);
            }
            else
            {
                limitL = ((sz_bloque)*inicio_bloque) + 1;
                limitR = ((sz_bloque)*inicio_bloque) + anterior;
            }
            //cout << "Ronda: " << k << " Con: " << i << " Se agarra a vergazos contra : \n";
            ld proba = 0;
            for(int j = limitL; j <= limitR; j++)
            {
                //cout << j << " ";
                //if(i!=j)
                {
                    proba += dp[j][k-1]*aux[i-1] / (aux[i-1] + aux[j-1]);
                    assert(aux[i-1] + aux[j-1] >= 1);
                }
            }
            //cout << endl;
            dp[i][k] = dp[i][k-1]*proba;
        }
    }


    cout << fixed << setprecision(9) << dp[1][levels] << endl;
    

    
	return 0;
}