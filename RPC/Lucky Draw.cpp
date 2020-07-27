#include <bits/stdc++.h>
#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

ld dp[55][10005]; // dp[j][q] probabilidad de que un wey tenga j-vidas despues del turno q
// La probabilidad de que 1 wey gane es la proba que hay de que todos pierdan antes del t turno y yo no
//La probabilidad de que pierda es que en el t turno, tenga 0 vidas el wey

int main()
{
    fastIO();
    ld p;
    lli n, k;
    cin >> n >> k >> p;
    ld q = 1-p;

    dp[k][0] = 1;

    for(int j = k; j>=0; j--)
    {
        for(int t = 0; t<10000; t++)
        {
            if(j == 0)
            {
                dp[0][t+1] += dp[0][t];
            }
            else
            {
                dp[j][t+1] += dp[j][t]*p;   // probabilidad de llegar al (t+1)-esimo turno, con j vidas
                dp[j-1][t+1] += dp[j][t]*q;
            }
        
            //if(j > 0)
                //cerr << dp[j][1] << " " << (t+1) << endl;
        }
    }


    ld gano = 0;
    for(lli t = 1; t<10000; t++)
    {
        //for(int j = 1; j<=k; j++)
        {
          //  probVivo += dp[j][t]; // Probabilidad de que este vivo en la t-ronda el wey
        }
        ld probVivo = dp[0][t+1] - dp[0][t]; // Probabilidad de que se haya muerto en la t-ronda
        ld pierden = pow(dp[0][t], n-1);

        gano += pierden * probVivo; // La probabilidad de que en el t-esimo round, todos hayan perdido menos yo.
        //cerr << pierden << " " << probVivo << endl;;
        //cerr << gano << endl;
    }
    //cerr << "la proba de ganar es de " << gano << endl;

    ld res = 1 - n*(gano);
    cout << fixed << setprecision(10) << res << endl;

    
    
    return 0;
}