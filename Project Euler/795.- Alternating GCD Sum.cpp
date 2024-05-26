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


lli binPower(lli a, lli b) {
    lli res = 1;
    while(b) {
        if( b & 1 ) res = res * a;
        b >>= 1;
        a = a * a;
    }
    return res;
}

lli g(lli p, lli a) {
    return binPower(p, a/2);
}

vector<lli> sieveMulFunction(lli n)
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
            if(p == lp[i]){ // lowestPrime[i] == p
                f[d] = f[ i/pot[i] ] * g(p,cnt[i]+1);
                pot[d] = pot[i]*p;
                cnt[d] = cnt[i]+1;
                break;
            }
            else{ //Coprimes
                f[d] = f[i]*f[p];
                pot[d] = p;
                cnt[d] = 1;
            }
        }
    }
    return f;
}




lli h(lli k, lli d) {
    lli sum = 0;
    for(lli i = 1; i <= k*d; i++) {
        lli mult = i & 1 ? -1 : 1;
        if(i*i % d == 0) {
            sum += mult;
        }
    }
    return sum;
}



int main () {
	//fastIO();

    lli N; cin>>N;

    lli ans = 0;
    auto phi = phiSieve(N);
    auto g = sieveMulFunction(N);

    auto gauss = [](lli n) {
        return n*(n+1)/2;
    };
    
    for(int d = 1; d <= N; d++) {

        lli odd_sum = -1* (N/d)/2;
        if((N/d) % 2) odd_sum -= 1;

        lli even_sum = g[d] * gauss(N/d);

        lli sum = d & 1 ? odd_sum : even_sum;

        ans += phi[d] * sum;
    }
    cout << ans << endl;

	return 0;
}

