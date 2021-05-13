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

const int MOD = 999999017;

vector<lli> Phi;
void phiSieve(int n)
{
	Phi.resize(n + 1);
	for(int i = 1; i <= n; ++i) Phi[i] = i;
	for(int i = 2; i <= n; ++i)
		if(Phi[i] == i)
			for(int j = i; j <= n; j += i)
				Phi[j] -= Phi[j] / i;
}

lli binPow(lli a, lli b)
{
    lli res = 1;
    a %= MOD;
    while(b)
    {
        if(b&1) res = res*a%MOD;
        b>>=1;
        a=a*a%MOD;
    }
    return res;
}


/*	
    O(n^(2/3)) if precompute limit = n^(2/3)
    Prefix sum of multiplicative functions :
    p_f : the prefix sum of f (x) (1 <= x <= limit).
    p_g : the prefix sum of g (x) (0 <= x <= N).
    p_c : the prefix sum of f * g (x) (0 <= x <= N).
    limit : the thereshold, generally should be n ^ (2 / 3).
*/
struct Prefix_F{

	typedef lli (*func) (lli);

	func p_f, p_g, p_f_conv_g; //Funcion para obtener P_G y P_F_conv_G (Deben ir en corto)
	lli limit, inv;
	unordered_map <lli, lli> dp;

	Prefix_F(func p_f, func p_g, func p_f_conv_g, lli limit) : p_f (p_f), p_g (p_g), p_f_conv_g (p_f_conv_g), limit(limit) {}

	lli go(lli n) {
		if (n <= limit) return p_f (n);
		if (dp.count(n)) return dp[n];
		lli ans = 0;
		for (lli i = 2, r; i <= n; i = r + 1) {
			r = n / (n / i);
			ans += (p_g(r) - p_g(i - 1) + MOD)%MOD * go(n / i)%MOD;
            if(ans>=MOD) ans-=MOD;
		}
        assert(ans >= 0 && ans < MOD);
		ans = p_f_conv_g (n) - ans; ans = ans / inv;

		return dp[n] = ans;
	}

	lli get(lli n) {
		if (n <= 0) return 0;
		inv = p_g (1);
		return go(n); 
	}
};

vector<lli> F;

lli inv2 = binPow(2, MOD-2);
lli inv6 = binPow(6, MOD-2);

lli get_F(lli n)
{
    return F[n];
}

lli get_G(lli n)
{
    n %= MOD;
    return (n*(n+1)%MOD)*inv2%MOD;
}

lli get_F_conv_G(lli n)
{
    n %= MOD;
    return (n*(n+1)%MOD*(2*n%MOD+1)%MOD)*inv6%MOD;
}

int main () {
    lli n; cin>>n;

    clock_t begin = clock();

    lli limit = pow(n, 2.0/3.0);
    F.resize(limit+1);
    phiSieve(limit+1);

    for(lli i = 1; i<=limit; i++)
        F[i] = (F[i-1] + (i*Phi[i]%MOD))%MOD;


    Prefix_F T(get_F, get_G, get_F_conv_G, limit);

    lli ans = 0;
    for(lli i = 1, r; i<=n; i = r+1)
    {
        r = n/(n/i);
        ans += (T.get(r) - T.get(i-1) + MOD)%MOD*(n/i)%MOD;
        if(ans >= MOD) ans-=MOD;
    }
    
    n %= MOD;
    lli aux = (ans + n)%MOD;
    ans = aux*inv2%MOD;

    cout << ans << endl;
    cout << "Time: " << (double)(clock() - begin)/CLOCKS_PER_SEC << endl;
    
	return 0;
}