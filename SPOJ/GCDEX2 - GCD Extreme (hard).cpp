#include <bits/stdc++.h>
 
#define endl '\n'
#define ull long long unsigned int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<ull> VLL;
typedef vector<int> VI;


vector<ull> Phi;
void phiSieve(ull n)
{
	Phi.resize(n + 1);
	for(ull i = 1; i <= n; ++i) Phi[i] = i;
	for(ull i = 2; i <= n; ++i)
		if(Phi[i] == i)
			for(ull j = i; j <= n; j += i)
				Phi[j] -= Phi[j] / i;
}

struct Prefix_F{

	typedef ull (*func) (ull);

	func p_f, p_g, p_f_conv_g; //Funcion para obtener P_G y P_F_conv_G (Deben ir en corto)
	ull limit, inv;
	unordered_map <ull, ull> dp;

	Prefix_F(func p_f, func p_g, func p_f_conv_g, ull limit) : p_f (p_f), p_g (p_g), p_f_conv_g (p_f_conv_g), limit(limit) {}

	ull go(ull n) {
		if (n <= limit) return p_f (n);
		if (dp.count(n)) return dp[n];
		ull ans = 0;
		for (ull i = 2, r; i <= n; i = r + 1) {
			r = n / (n / i);
			ans += (p_g(r) - p_g(i - 1)) * go(n / i);
		}
		ans = p_f_conv_g (n) - ans; ans = ans / inv;

		return dp[n] = ans;
	}

	ull get(ull n) {
		if (n <= 0) return 0;
		inv = p_g (1);
		return go(n); 
	}
};



VLL prefix_Phi;

ull Gauss(ull n)
{
    ull aux1 = n, aux2 = n+1;
    if(aux1 % 2 == 0)  aux1 /= 2;
    else if(aux2 % 2 == 0) aux2 /= 2;
    else
    {
        assert(false);
    }
    return aux1*aux2;
}

ull get_prefix(ull n)
{
    return prefix_Phi[n];
}

ull get_g(ull n)
{
    return n;
}

Prefix_F *F;

void init(ull t)
{
    ull maxN = 235711131719;
    ull limit;
    if(t <= 1000)
    {
        limit = pow(maxN, 2.0/3.0);    
    }
    else
    {
        limit = 1e7;
    }
    
    phiSieve(limit+5);
    prefix_Phi.resize(limit+5);

    for(ull i = 1; i<= limit; i++)
    {
        prefix_Phi[i] = (prefix_Phi[i-1] + Phi[i]) ;
    } 
    F = new Prefix_F(get_prefix, get_g, Gauss, limit);
}

int main () {
	fastIO();

    ull t; cin>>t;
    init(t);
    for(ull i = 0; i<t; i++)
    {
        ull n; cin>>n;
        ull ans = 0;
        
        for(ull i = 1, r; i<=n; i = r+1)
        {
            r = n/(n/i);
            ans += (F->get(r) - F->get(i-1)) * Gauss(n/i);
        }
        ans -= Gauss(n);
        assert(ans >= 0);
        cout << ans << endl;
    } 


	return 0;
}
