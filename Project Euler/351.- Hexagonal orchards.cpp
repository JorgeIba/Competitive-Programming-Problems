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


vector<lli> phiSieve(int n){
	vector<lli> Phi(n+1);
	iota(Phi.begin(), Phi.end(), 0);
	for(int i = 2; i <= n; ++i)
		if(Phi[i] == i)
			for(int j = i; j <= n; j += i)
				Phi[j] -= Phi[j] / i;
	return Phi;
}



const lli n = 1e8;
lli limit = pow(n, 2.0/3.0);
auto phi = phiSieve(limit);
auto prefixPhiLower = phi;

lli Gauss(lli n) {
    return n*(n+1)/2;
}

map<lli,lli> dp;
lli prefixPhi(lli n){
    if(n <= limit) return prefixPhiLower[n];
    if(dp.count(n)) return dp[n];
    
    lli sum = 0;
    for(lli d = 2, r; d <= n; d = r+1) {
        r = n / (n / d);

        sum += (r - d + 1) * prefixPhi(n / d);
    }

    return dp[n] = Gauss(n) - sum;
}



int main () {
	//fastIO();
	partial_sum(all(prefixPhiLower), prefixPhiLower.begin());

    

    lli total_points = Gauss(n+1) - 1;
    // lli coprimes = prefixPhiLower[n] + 1;
    lli coprimes = prefixPhi(n) + 1;
    lli horizon = 2 * (n-1);

    lli total_per_triangle = total_points - coprimes - horizon;
    lli ans = 6 * ( total_per_triangle + horizon/2 );


    cout << ans << endl;

	return 0;
}

