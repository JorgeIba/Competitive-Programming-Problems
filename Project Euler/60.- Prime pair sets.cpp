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

vector<int> primes;
vector<bool> isPrime;
void primesSieve(int n)
{
	isPrime.resize(n + 1, true);
	isPrime[0] = isPrime[1] = false;
	primes.push_back(2);
	for(int i = 4; i <= n; i += 2) isPrime[i] = false;
	for(lli i = 3; i <= n; i += 2)
    {
		if(isPrime[i])
        {
			primes.push_back(i);
			if(i * i <= n)
				for(int j = i * i; j <= n; j += 2 * i)
					isPrime[j] = false;
		}
	}
}

const int INF = 1e9, maxN = 1e6, maxLook=1100;

lli mul(lli a, lli b, lli mod)
{
    a%=mod;
    b%=mod;
    if(a < 1e9 && b < 1e9) return a*b%mod;
    lli res = 0;
    while(b)
    {
        if(b&1) res = (res+a) %mod;
        b>>=1;
        a= (a+a)%mod;
    }
    return res;
}

lli binPow(lli a, lli b, lli mod)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = mul(res, a, mod);
        b>>=1;
        a = mul(a,a,mod);
    }
    return res;
}

//22
bool isPrimeMillerRabin(lli n)
{
    if(n < 2) return false;
    if( ~n & 1) return false;
    lli d = n-1, s = 0; //n-1 = 2^s*k
    for(;(~d&1); d>>=1, s++); //d = k
    for(lli a: {2, 3, 5, 7, 11, 13, 17})
    {
        if(n == a) return true;
        lli residuo = binPow(a, d, n);
        if(residuo == 1 or residuo == n-1) continue;
        lli x = s;
        while(--x)
        {
            residuo = mul(residuo, residuo, n);
            if(residuo == n-1) break;
        }
        if(x==0) return false;
    }
    return true; //Probability = 1 - (1/4)^size_of(vector_a)
}

bool is_prime(lli n)
{
    if(n < maxN) return isPrime[n];
    return isPrimeMillerRabin(n);
}


lli f(lli idx, vector<lli> ps)
{
    if(SZ(ps) == 5)
    {
        lli ans = 0;
        for(auto x: ps)
        {
            cout << x << " ";
            ans += x;
        } 
        cout << endl;
        return ans;
    }
    if(idx > maxLook) return INF;

    lli prime = primes[idx];
    string sprime = to_string(prime);

    bool can = true;
    for(auto x: ps)
    {
        string sx = to_string(x);
        string sbefore = sprime + sx;
        string safter = sx + sprime;
        lli before = stoll(sbefore), after = stoll(safter);
        if(is_prime(before) && is_prime(after)) continue;
        else can = false;
    }
    lli no = f(idx+1, ps), si = INF;
    if(can) 
    {
        ps.push_back(prime);
        si = f(idx+1, ps);
    }
    return min(no, si);
}

int main () {
	//fastIO();
    time_t begin = clock();
    primesSieve(maxN);
    VLL aux;
    cout << f(1, aux) << " " << (double) (clock() - begin) / CLOCKS_PER_SEC <<  endl;
    
	return 0;
}