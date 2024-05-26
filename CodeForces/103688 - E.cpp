#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;


const int MOD = 1e9+7;

template<class Fun>
vector<lli> sieveMulFunction(lli n, Fun g)
{
    vector<lli> primes, lp(n+1), f(n+1), cnt(n+1), pot(n+1);
    f[1] = 1;
    for(int i = 2; i<=n; i++){
        if(!lp[i]){
            lp[i] = pot[i] = i; cnt[i] = 1;
            f[i] = g(i,1);
            primes.push_back(i);
        }
        for(auto p: primes){
            lli d = i*p;
            if(d>n) break;
            lp[d] = p;
            if(p == lp[i]){ 
                f[d] = f[ i/pot[i] ] * g(p,cnt[i]+1); 
                pot[d] = pot[i]*p;
                cnt[d] = cnt[i]+1;
                break;
            }
            else{ 
                f[d] = f[i]*f[p]; 
                pot[d] = p;
                cnt[d] = 1;
            }
        }
    }
    return f;
}

template<int mod = MOD, typename T = int>
vector<T> gcdConvolution(const vector<T> &a, const vector<T> &b) {
    int n = SZ(a);

    vector<T> A(n+1), B(n+1), G(n+1);
    for(int g = 1; g <= n; g++) {
        for(int k = g; k <= n; k += g) {
            A[g] = (A[g] + a[k-1]) % mod;
            B[g] = (B[g] + b[k-1]) % mod;
        }
        G[g] = 1LL * A[g] * B[g] % mod;
    }

    vector<T> dp_g(n);
    for(int i = n; i >= 1; i--) {

        dp_g[i-1] = G[i];

        for(int k = 2*i; k <= n; k += i) {
            dp_g[i-1] = (dp_g[i-1] - dp_g[k-1] + mod) % mod;
        }
    }
    return dp_g;
}


lli powerMod(lli a, lli b){
    lli res = 1;
    while(b){
        if(b&1) res = res * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return res;
}


const int MAXA = 2e5+100;

int main () {
	fastIO();

    vector<lli> inv(MAXA+1, 1);
    for(int i = 2; i <= MAXA; ++i){
        inv[i] = MOD - (MOD/i)*inv[MOD%i]%MOD;
	}
    
    int n; cin>>n;
    vector<int> A(n);

    for(auto &x: A) cin>>x;

    auto f = sieveMulFunction(MAXA, [](int p, int a){
        return (a & 1 ? p : 1);
    });

    vector<int> C(MAXA);
    for(int i = 0; i < n; i++) {
        auto a = A[i];
        (C[f[a]-1] += f[a]) %= MOD;
    }

    auto CONV = gcdConvolution(C, C);

    int sum_good = 0;

    for(int i = 1; i <= MAXA; i++) {
        sum_good += 1LL * CONV[i-1] * inv[i] % MOD * inv[i] % MOD;
        if(sum_good >= MOD) sum_good -= MOD;
    }

    for(int i = 0; i < n; i++) {
        sum_good -= 1;
        if(sum_good < 0) sum_good += MOD;
    }

    int inv_2 = (MOD+1)/2;

    cout << 1LL * sum_good*inv_2 % MOD << endl;


	return 0;
}

