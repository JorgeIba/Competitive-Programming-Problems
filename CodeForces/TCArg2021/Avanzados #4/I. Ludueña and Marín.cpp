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


unsigned long long mulMod( unsigned long long a,
                            unsigned long long b,
                            unsigned long long m){

    unsigned long long res = 0, tmp = a % m;

    while (b)
    {
        if (b & 1)
        {
            res = res + tmp;
            res = (res >= m ? res - m : res);
        }
        b >>= 1;
        tmp <<= 1;
        tmp = (tmp >= m ? tmp - m : tmp);
    }

    return res;
}

long long powMod(long long a, long long b, long long m){
    long long res = 1 % m, tmp = a % m;
    while (b)
    {
        if (b & 1)
        {
            //res = (res * t) % m;
            res = mulMod(res, tmp, m);
        }
        //t = t * t % m;
        tmp = mulMod(tmp, tmp, m);
        b >>= 1;
    }
    return res;
}

bool millerRabin(long long n){
    int a[5] = { 2, 3, 7, 61, 24251 };

    if (n == 2) return true;
    if (n == 1 || (n & 1) == 0) return false;

    long long b = n - 1;

    for (int i = 0; i < 5; i++)
    {
        if (a[i] >= n) break;

        while ((b & 1) == 0) b >>= 1;

        long long t = powMod(a[i], b, n);

        while (b != n - 1 && t != 1 && t != n - 1){
            t = mulMod(t, t, n);
            b <<= 1;
        }

        if (t == n - 1 || (b & 1)) continue;
        else return false;
    }
    return true;
}

long long gcd(long long a, long long b){
    while (b > 0){
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

long long pollard_rho(long long n){

    long long x = 2 % n, y = x, k = 2, i = 1;
    long long d = 1;

    while (true)
    {
        i++;
        x = (mulMod(x, x, n) + 1) % n;
        d = gcd((y - x + n) % n, n);

        if (d > 1 && d < n)
        {
            return d;
        }

        if (y == x)
        {
            long long d = 2;
            while (n % d) d++;
            return d;
        }

        if (i == k)
        {
            y = x;
            k <<= 1;
        }
    }
}



unordered_map<lli,lli> factors;
void _factorize(long long n){
    if (n <= 1) return;

    if (millerRabin(n)){
        factors[ n ]++;
        return;
    }

    long long d = pollard_rho(n);
    _factorize(d);
    _factorize(n / d);
}

void factorize(long long n)
{
    factors.clear();
    _factorize(n);
}

lli power(lli b, lli e){
	lli ans = 1;
	while(e){
		if(e & 1) ans *= b;
		e >>= 1;
		b *= b;
	}
	return ans;
}


//number of coprimes with n less than n
lli phi(lli n){
	lli ans = n;
	factorize(n);
	for(auto & factor : factors)
		ans -= ans / factor.first;
	return ans;
}


// the smallest positive integer k such that x^k = 1 mod m
lli multiplicativeOrder(lli x, lli m){
	if(gcd(x, m) != 1) return 0;
	lli order = phi(m);
	factorize(order);
	for(auto & factor : factors){
		lli p = factor.first;
		int a = factor.second;
		order /= power(p, a);
		lli tmp = powMod(x, order, m);
		while(tmp != 1){
			tmp = powMod(tmp, p, m);
			order *= p;
		}
	}
	return order;
}


int main () {
	//fastIO();

	lli a, m; cin>>a>>m;

    
    if(__gcd(a, m) != 1 || m == 1)
    {
        cout << "Maradona e muito mais grande que o Pele" << endl;
        return 0;
    }

    if( a == 1 )
    {
        cout << 1 << endl;
        return 0;
    }

 
    cout << multiplicativeOrder(a, m) << endl;
    
	return 0;
}

