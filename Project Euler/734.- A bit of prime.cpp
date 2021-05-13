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

const int p = 1e9+7;
const int MOD = 1e9+7;

//Fast Walsh-Hadamard transform, works with any modulo p
//op: 0(OR), 1(AND), 2(XOR), A.size() must be power of 2
void fwt(VLL & A, int op, int inv){
	int n = A.size();
	for(int k = 1; k < n; k <<= 1)
		for(int i = 0; i < n; i += k << 1)
			for(int j = 0; j < k; ++j){
				int u = A[i + j], v = A[i + j + k];
				int sum = u + v < p ? u + v : u + v - p;
				int rest = u - v < 0 ? u - v + p : u - v;
				if(inv == -1){
					if(op == 0)
						A[i + j + k] = rest ? p - rest : 0;
					else if(op == 1)
						A[i + j] = rest;
					else if(op == 2)
						A[i + j] = sum, A[i + j + k] = rest;
				}else{
					if(op == 0)
						A[i + j + k] = sum;
					else if(op == 1)
						A[i + j] = sum;
					else if(op == 2)
						A[i + j] = sum, A[i + j + k] = rest;
				}
			}
}

vector<bool> isPrime;
void primesSieve(int n)
{
	isPrime.resize(n + 1, true);
	isPrime[0] = isPrime[1] = false;
	for(int i = 4; i <= n; i += 2) isPrime[i] = false;
	for(lli i = 3; i <= n; i += 2)
    {
		if(isPrime[i])
			if(i * i <= n)
				for(int j = i * i; j <= n; j += 2 * i)
					isPrime[j] = false;
	}
}


VLL binPow(VLL P, lli b)
{
    VLL R(SZ(P)); 
    R[0] = 1;

    fwt(R, 0, 1);
    fwt(P, 0, 1);
    while(b)
    {
        if(b&1)
        {
            for(int i = 0; i<SZ(P); i++) R[i] = R[i]*P[i] %MOD;
        }
        b>>=1;
        for(int i = 0; i<SZ(P); i++) P[i] = P[i]*P[i] %MOD;
    }
    fwt(R, 0, -1);
    return R;
}

int main () {
	//fastIO();
    
    lli n = 1e6, N = (1<<20), k = 999983;
    //cin >> n >> k;
    primesSieve(n);

    vector<lli> Poly(N);
    for(int i = 1; i<=n; i++) Poly[i] = isPrime[i];

    Poly = binPow(Poly, k);

    lli ans = 0;
    for(int i = 1; i<=n; i++) ans = (ans + (isPrime[i])*Poly[i])%MOD;
    
    cout << ans << endl;

	return 0;
}