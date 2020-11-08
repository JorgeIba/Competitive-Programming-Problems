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

vector<lli> PrefixFunction(string &t, int l, int r)
{
    string s = t.substr(l, r-l+1);
    //cout << s << endl;
    lli n = s.length();
    vector< lli > pi(n);
    pi[0] = 0;
    for(int i = 1; i<n; i++)
    {
        lli j = pi[i-1];
        while(j>0 && s[i] != s[j]) j = pi[j-1];
        if(s[i]!=s[j]) pi[i] = 0;
        else pi[i] = j + 1;
    }
    return pi;
}

lli n;
string s; 


lli compress[710][710]; //compress[i][j] -> smallest compression from i to j

void compression()
{
    for(int L = 0; L<n; L++)
    {
        for(int R = L; R<n; R++)
        {
            auto pi = PrefixFunction(s, L, R);
            int auxN = R - L + 1;
            compress[L][R] = auxN - pi[auxN-1];
            if(auxN % compress[L][R] != 0) compress[L][R] = auxN;
        }
    }
}

lli dp[750][750];
const lli INF = 1e18;

int main () {
	fastIO();
    cin>>n;
    cin>>s;
    compression();
    /*
    while(true)
    {
        lli l, r; cin>>l>>r;
        cout << compress[l][r] << endl;
    }
    */
    
    
    for(int i = 0; i<750; i++) for(int j = 0; j<750; j++) dp[i][j] = INF;

    for(int i = 0; i<750; i++) dp[i][i] = 1;

    for(int L = n-1; L>=0; L--)
    {
        for(int R = L; R<=n; R++)
        {
            for(int k = L; k<=R; k++)
            {
                lli bestC = compress[L][k];
                lli bestPoints = dp[k-bestC+1][k];
                dp[L][R] = min(dp[L][R], bestPoints + (k+1>R?0:dp[k+1][R]));
                //lli aux = dp[L][R];
                
                if(L == 11 && R == 13)
                {
                    //cout << L << "-" << k << ",  " << k+1 << " - " << R << ", " << bestC << ", " << bestPoints << ", " << dp[k+1][R] << endl;
                    //cout << endl;
                }
                
            }
        }
    }
    //cout << dp[11][13] << endl;
    cout << dp[0][n-1] << endl;
    

	return 0;
}