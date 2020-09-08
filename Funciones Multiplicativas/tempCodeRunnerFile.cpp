#include <bits/stdc++.h>
#define int128 __int128
#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli MOD = 1e9 + 7;

int128 modularInverse(lli a, lli m){
	int128 r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(r0 < 0) s0 *= -1;
	if(s0 < 0) s0 += m;
	return s0;
}


int128 powerMod(int128 b, int128 e, int128 m){
	int128 ans = 1;
	b %= m;
	if(e < 0){
		b = modularInverse(b, m);
		e *= -1;
	}
	while(e){
		if(e & 1) ans = (ans * b) % m;
		e >>= 1;
		b = (b * b) % m;
	}
	return ans;
}




bool isPrimeMillerRabin(lli n){
	if(n < 2) return false;
	if(!(n & 1)) return n == 2;
	lli d = n - 1, s = 0;
	for(; !(d & 1); d >>= 1, ++s);
	for(int a : {2, 3, 5, 7, 11, 13, 17}){
		if(n == a) return true;
		int128 m = powerMod(a, d, n);
		if(m == 1 || m == n - 1) continue;
		int k = 0;
		for(; k < s; ++k){
			m = m * m % n;
			if(m == n - 1) break;
		}
		if(k == s) return false;
	}
	return true;
}


mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
lli aleatorio(lli a, lli b){
	std::uniform_int_distribution<lli> dist(a, b);
	return dist(rng);
}

lli getFactor(lli n){
	lli a = aleatorio(1, n - 1), b = aleatorio(1, n - 1);
	lli x = 2, y = 2, d = 1;
	while(d == 1){
		x = x * (x + b) % n + a;
		y = y * (y + b) % n + a;
		y = y * (y + b) % n + a;
		d = __gcd(abs(x - y), n);
	}
	return d;
}

map<lli, int> fact;
void factorizePollardRho(lli n, bool clean = true){
	if(clean) fact.clear();
	while(n > 1 && !isPrimeMillerRabin(n)){
		lli f = n;
		for(; f == n; f = getFactor(n));
		n /= f;
		factorizePollardRho(f, false);
		for(auto & it : fact){
			while(n % it.first == 0){
				n /= it.first;
				++it.second;
			}
		}
	}
	if(n > 1) ++fact[n];
}

int128 g(lli p, lli a){
    int128 pa = powerMod(p,a,MOD);
    return (-1*pa * (pa-1) + pa*pa)%MOD  ;
}

int128 f(lli p, lli a){
    int128 pa = powerMod(p,a,MOD);
    int128 aux = (pa*pa - 1) / (p+1);
    return (-pa*aux + pa*pa*pa) %MOD;
}

int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--)
    {
        lli n; cin>>n;
        int128 F=1, G=1;
        if(n==1)
        {
            cout<<1<<endl;
            continue;
        } 
        factorizePollardRho(n);
        for(auto x: fact)
        {
            F = (F * f(x.first, x.second)) %MOD;
            G = (G* g(x.first, x.second)) % MOD;
        }
        lli res = (F + G)%MOD;
        cout<< res/2 <<endl;
    }
    return 0;
}