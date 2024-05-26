#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef __int128 lli;
typedef long double ld;


ostream &operator<<(ostream &os, const __int128 & value){
	char buffer[64];
	char *pos = end(buffer) - 1;
	*pos = '\0';
	__int128 tmp = value < 0 ? -value : value;
	do{
		--pos;
		*pos = tmp % 10 + '0';
		tmp /= 10;
	}while(tmp != 0);
	if(value < 0){
		--pos;
		*pos = '-';
	}
	return os << pos;
}

vector<int> muSieve(int n){
	vector<int> Mu(n+1, -1);
	Mu[0] = 0, Mu[1] = 1;
	for(int i = 2; i <= n; ++i)
		if(Mu[i])
			for(int j = 2*i; j <= n; j += i)
				Mu[j] -= Mu[i];
	return Mu;
}

struct Prefix_F {

    typedef lli (*func)(lli);

    func p_f, p_g,
        p_f_conv_g; // Funcion para obtener P_G y P_F_conv_G (Deben ir en corto)
    lli limit, inv;
    map<lli, lli> dp;

    Prefix_F(func p_f, func p_g, func p_f_conv_g, lli limit)
        : p_f(p_f), p_g(p_g), p_f_conv_g(p_f_conv_g), limit(limit) {}

    lli go(lli n) {
        if (n <= limit)
            return p_f(n);
        if (dp.count(n))
            return dp[n];
        lli ans = 0;
        for (lli i = 2, r; i <= n; i = r + 1) {
            r = n / (n / i);
            ans += (p_g(r) - p_g(i - 1))* go(n / i);
        }
        // assert(ans >= 0 && ans < MOD);
        ans = p_f_conv_g(n) - ans;
        ans = ans / inv;

        return dp[n] = ans;
    }

    lli get(lli n) {
        if (n <= 0)
            return 0;
        inv = p_g(1);
        return go(n);
    }
};


const lli N = 1e10;
const int LIMIT = pow(N, 2.0 / 3.0);
auto mu = muSieve(LIMIT+1);
vector<int> prefix_mu = mu;

Prefix_F *F;

lli p_f(lli n) {
    return prefix_mu[n];
}

lli p_g(lli n){
    return n;
}

lli p_fg(lli n) {
    return 1;
}

lli G(lli n) {
    return F->get(n);
}

lli g(lli n){
    return mu[n];
}


lli f(lli n) {
    return (n * n * n + 3 * n * n + 3 * n);
}


int main () {
	// fastIO();

    partial_sum(all(prefix_mu), prefix_mu.begin());

    // const lli MOD = 1e13;
    
    lli ans = 0;

    F = new Prefix_F(p_f, p_g, p_fg, LIMIT);
    ans = 0;

    lli m = sqrtl(N);
    for(int i = 1; i <= N/m; i++) {
        (ans += f(N / i) * g(i));
    }

    for(int i = 1; i <= m-1; i++) {
        (ans += f(i) * (G(N / i) - G(N / (i+1))));
    }

    cout << ans << endl;


	return 0;
}

