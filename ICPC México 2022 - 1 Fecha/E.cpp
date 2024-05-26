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



const lli MOD = 1e9+7;

//13
const lli maxN = 1e6+10;
vector<lli> fact(maxN+1, 1), inv(maxN+1, 1), invFact(maxN+1,1);
void prec()
{
    for(lli i = 2; i < maxN; ++i)
    {
        fact[i] = i*fact[i-1] %MOD;
        inv[i] = MOD - (MOD/i)*inv[MOD%i]%MOD;
        invFact[i] = (lli)inv[i]*invFact[i-1]%MOD;
	}
}


lli nCr(lli n, lli r) {
    if(r < 0 || n < r) return 0;
    return fact[n] * invFact[n-r] % MOD * invFact[r] % MOD;
}


lli binPow(lli a, lli b, lli mod){
    lli res = 1;
    while(b) {
        if(b & 1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}


int main () {
	//fastIO();

    prec();


    lli N, M, K; cin>>N>>M>>K;

    // lli total = binPow(K, N, MOD);

    vector<lli> take_off(K+1);

    for(int i = 0; i <= K; i++) {
        lli how_many_ways = nCr(K, i);
        take_off[i] = binPow(K-i, N, MOD) * how_many_ways % MOD;
    }

    // for(int i = 0; i <= K; i++) cout << take_off[i] << " ";

    lli ans = 0;

    for(lli i = 0; i <= K; i++) {
        lli sum = take_off[i];

        if(i % 2 == 0) {
            ans = (ans + sum) % MOD;
        } else {
            ans = (ans - sum) % MOD;
            if(ans < 0) ans += MOD;
        }
    }


    cout << ans*nCr(M, K) % MOD << endl;



	return 0;
}

