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


const lli maxN = 1e6+10;
vector<lli> ans(maxN);
const lli MOD = 1e9+7;
lli pow2[maxN];

void prec()
{
    pow2[0] = 1;
    for(lli i = 1; i<maxN; i++) pow2[i] = 2*pow2[i-1] % MOD;

    for(lli i = 1; i < maxN; i++)
    {
        for(lli j = 2; j*i < maxN; j++)
        {
            ans[i*j] += pow2[i];
            if(ans[i*j] >= MOD) ans[i*j] -= MOD;
            ans[i*j] -= ans[i];
            if(ans[i*j] < 0) ans[i*j] += MOD;
        }
    }
}


int main () {
	fastIO();
    prec();

    lli t; cin>>t;

    while(t--)
    {
        lli n; cin>>n;
        if(n == 1) cout << 0 << endl;
        else 
        {
            cout << ans[n] << endl;
        }
    }


	return 0;
}

