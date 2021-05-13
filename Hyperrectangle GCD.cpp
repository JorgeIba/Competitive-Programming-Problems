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

const int MOD = 1e9+7;

vector<int> Phi;
void phiSieve(int n)
{
	Phi.resize(n + 1);
	for(int i = 1; i <= n; ++i) Phi[i] = i;
	for(int i = 2; i <= n; ++i)
		if(Phi[i] == i)
			for(int j = i; j <= n; j += i)
				Phi[j] -= Phi[j] / i;
}

const int maxA = 1e5+5;

int main () {
	fastIO();
    phiSieve(maxA);
    vector<lli> prefix(maxA);
    for(int i = 1; i<maxA; i++) prefix[i] = (prefix[i-1] + Phi[i])%MOD;
    lli t; cin>>t;
    while(t--)
    {
        lli k; cin>>k;
        vector<lli> limits(k);
        for(auto &x: limits) cin>>x;
        lli minimo = *min_element(all(limits));
        lli ans = 0;
        for(lli d = 1, r; d<=minimo; d = r+1)
        {
            lli aux1 = 1;
            r = 1e9;
            for(auto Ai: limits)
            {
                lli lAi = Ai/d, rAi = Ai/lAi;
                aux1 = aux1*(int(Ai/d))%MOD;
                r = min(r, rAi);
            }
            //cout << r << " " << d-1 << endl;
            ans += (prefix[r] - prefix[d-1] + MOD)%MOD * aux1 % MOD;
            //ans += Phi[d]*aux1%MOD;
            if(ans >= MOD) ans -= MOD;
        }
        cout << ans << endl;
    }
    
	return 0;
}