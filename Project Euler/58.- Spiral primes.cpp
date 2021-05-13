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

lli binPow(lli a, lli b, lli mod)
{
	a %= mod;
	lli res = 1;
	while(b)
	{
		if(b&1) res = res * a %mod;
		b>>=1;
		a = a*a%mod;
	}
	return res;
}

bool isPrime(lli n)
{
    if(n < 2) return false;
    if( ~n & 1) return false;
    lli d = n-1, s = 0; //n-1 = 2^s*k
    for(;(~d&1); d>>=1, s++); //d = k
    for(lli a: {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
    {
        if(n == a) return true;
        lli residuo = binPow(a, d, n);
        if(residuo == 1 or residuo == n-1) continue;
        lli x = s;
        while(--x)
        {
            residuo = (residuo * residuo) % n;
            if(residuo == n-1) break;
        }
        if(x==0) return false;
    }
    return true; //Probability = 1 - (1/4)^size_of(vector_a)
}


const int maxL = 1e6+1;

int main () {
	//fastIO();
	//primesSieve(maxN);

	vector<lli> f(maxL+1), g(maxL+1), h(maxL+1);
	f[0] = 3;
	g[0] = 5;
	h[0] = 7;

	int diff_f = 10, diff_g = 12, diff_h = 14;

	
	int count_primes = 3;
	for(int n = 1; ; n++)
	{
		f[n] = f[n-1] + 8*(n-1) + diff_f;
		g[n] = g[n-1] + 8*(n-1) + diff_g;
		h[n] = h[n-1] + 8*(n-1) + diff_h;
		count_primes += (isPrime(f[n]) + isPrime(g[n]) + isPrime(h[n]));
		ld ratio = (ld)count_primes / (4*(n+1) + 1);
		if(ratio < 0.1)
		{
			cout << ratio << " " << (g[n] - f[n] + 1) << endl;
			break;
		}
	}

    
	return 0;
}