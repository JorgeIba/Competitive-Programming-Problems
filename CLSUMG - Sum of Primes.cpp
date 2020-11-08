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

int nearestPowerTwo(int n)
{
    int r = 1;
    while(r < n) r<<=1;
    return r;
}

lli powerMod(lli a, lli b, lli mod){
	lli res = 1;
	b %= mod-1;
	if(b < 0) b += mod-1;
	while(b){
		if(b & 1) res = (res * a) % mod;
		b >>= 1;
		a = (a * a) % mod;
	}
	return res;
}
 
template<int p, int g, typename T>
void ntt(vector<T> & A, bool inv){ //O(n log n)
	int n = SZ(A);
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(A[i], A[j]);
	}

	vector<lli> wp(n>>1, 1);

	for(int k = 1; k < n; k <<= 1){
		lli wk = powerMod(g, (inv?-1:1) * (p - 1) / (k<<1), p);
		for(int j = 1; j < k; ++j)
			wp[j] = (wp[j - 1] * wk) % p;

		for(int i = 0; i < n; i += k << 1){
			for(int j = 0; j < k; ++j){
				lli u = A[i + j], v = (A[i+j+k] * wp[j]) % p;
				A[i+j] = (u + v < p) ? u + v : u + v - p;
				A[i+j+k] = (u - v >= 0) ? u - v: u - v + p;
			}
		}
	}

	if(inv){
		lli inv_n = powerMod(n, p - 2, p);
		for(auto &x: A) x = (x*inv_n)%p;
	}
}
 
template<int p=167772161, int g=17, typename T>
vector<T> multiply(vector<T> A){ //O(n logn) it uses NTT
	int sz = SZ(A) + SZ(A) - 1;
	int size = nearestPowerTwo(sz);
    
	A.resize(size);
	ntt<p, g>(A, false);
	for(int i = 0; i < size; i++)
		A[i] = (lli)A[i] * A[i] % p;
	ntt<p, g>(A, true);

	A.resize(sz);
	return A;
}

const int maxN = 1e6 + 5;
//35
bool isPrime[maxN];
void primesSieve(int n)
{
	isPrime[0] = isPrime[1] = 1;
	for(int i = 4; i <= n; i += 2) isPrime[i] = 1;
	for(lli i = 3; i <= n; i += 2)
    {
		if(!isPrime[i])
        {
			if(i * i <= n)
				for(int j = i * i; j <= n; j += 2 * i)
					isPrime[j] = 1;
		}
	}
}


int main () {
	fastIO();
    primesSieve(maxN-1);
    vector<lli> A(maxN);
    for(int i = 0; i<maxN; i++)
        A[i] = !isPrime[i];
    
    A = multiply(A);
    A.resize(maxN);

    for(int i = 0; i<=maxN; i++)
    {
        lli quitar = 0;
        if(i%2==0 && !isPrime[i/2])
            quitar = (A[i]-1)/2;
        else
            quitar = A[i]/2;
        A[i] -= quitar;
    }

    lli t; cin>>t;
    while(t--)
    {
        lli n; cin>>n;
        lli suma = 0;
        vector<lli> fr(maxN);
        for(int i = 0; i<n; i++)
        {
            fr[A[i]]++;
            if(A[n] - A[i] >= 0)
                suma += fr[ A[n] - A[i]  ];

        }
        cout << suma << endl;
    }
	return 0;
}

//f(a) + f(b) = f(N)
//f(b) = f(N) - f(a)