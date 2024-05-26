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

tuple<lli, lli, lli> extendedGcd(lli a, lli b){
	if(b == 0){
		if(a > 0) return {a, 1, 0};
		else return {-a, -1, 0};
	}else{
		auto[d, x, y] = extendedGcd(b, a%b);
		return {d, y, x - y*(a/b)};
	}
}

int main () {
	fastIO();
	
    lli n, m; cin>>n>>m;
    vector<lli> nums(n);

    for(auto &a: nums) cin>>a;

    lli sum = 0;
    for(auto &a: nums) (sum += a) %= m;

    lli gauss = n*(n+1)/2;

    lli g = gcd(n, gauss);
    lli G = gcd(g, m);

    lli n_p = n / g;
    lli gauss_p = gauss / g;

    lli g_p = g / G;
    lli m_p = m / G;

    lli q_2 = (m - sum) / G;
    if( (m - sum) % G ) {
        q_2++;
    }

    lli ans = (sum + G * q_2) % m;
    auto [_, x_1, y_1] = extendedGcd(g_p, m_p);
    lli q_1 = x_1 * q_2 % m;
    // lli l   = y_1 * q_2; 

    auto [_2, x, y] = extendedGcd(n_p, gauss_p);
    lli s = x * q_1 % m;
    lli d = y * q_1 % m;

    cout << ans << endl;
    cout << (s+m)%m << " " << (d + m)%m << endl;
    
	return 0;
}

