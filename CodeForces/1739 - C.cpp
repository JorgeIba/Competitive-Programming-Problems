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

const lli maxN = 100;
const lli MOD = 998244353; // Initialize

//15
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
                nCr[i][j] = (nCr[i-1][j-1] + nCr[i-1][j]) % MOD;
            }
            //cout << nCr[i][j] << " ";
        }
        //cout << endl;
    }
}


int main () {
	//fastIO();
    prec();

    vector<pair<lli,lli>> dp(31);
    dp[1] = {1, 0};

    for(int i = 2; i <= 30; i++) {
        lli n = i*2;
        lli wins = nCr[n-1][n/2 - 1];
        auto [w, l] = dp[i-1];

        swap(w, l);

        lli new_wins = (w + wins) % MOD;

        dp[i] = {new_wins, (nCr[n][n/2] - new_wins - 1 + MOD) % MOD };
    }


    lli t; cin>>t;

    while(t--) {
        lli n; cin>>n;
        cout << dp[n/2].first << " " << dp[n/2].second << " " << 1 << endl;
    }



	return 0;
}

