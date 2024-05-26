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


vector<int> lowestPrime;
void lowestPrimeSieve(int n){
	lowestPrime.resize(n + 1, 1);
	lowestPrime[0] = lowestPrime[1] = 0;
	for(int i = 2; i <= n; ++i) lowestPrime[i] = (i & 1 ? i : 2);
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2)
		if(lowestPrime[i] == i)
			for(int j = i * i; j <= n; j += 2 * i)
				if(lowestPrime[j] == j) lowestPrime[j] = i;
}


lli powerMod(lli a, lli b, lli mod){
    lli res = 1;
    while(b){
        if(b&1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}

const int MOD = 1e9+7, p = MOD;

//Fast Walsh-Hadamard transform, works with any modulo p
//op: 0(OR), 1(AND), 2(XOR), A.size() must be power of 2
void fwt(vector<int> & A, int op, int inv){
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
	if(inv == -1 && op == 2){
		lli nrev = powerMod(n, p-2, p);
		for(int i = 0; i < n; ++i)
			A[i] = A[i] * nrev % p;
	}
}

const int MAXLOG = 20;

typedef vector<int> Poly;

Poly power(Poly A, int b){
    int n = SZ(A);
    Poly res(n); res[0] = 1;
    fwt(res, 2, 1);
    fwt(A, 2, 1);

    while(b){
        if(b & 1)
            forn(i, n)
                res[i] = 1LL*res[i] * A[i] % MOD;

        forn(i, n)
            A[i] = 1LL*A[i] * A[i] % MOD;

        b >>= 1;
    }

    fwt(res, 2, -1);
    return res;
}

int main () {
	//fastIO();

    // int n; cin>>n;
    // int k; cin>>k;

    const int n = 1e7, k = 1e7;

    lowestPrimeSieve(n);

    vector<int> grundy(n);
    grundy[0] = 0;
    grundy[1] = 1;
    grundy[2] = 0;
    
    for(int i = 3, j = 2; i < n; i++){
        if(lowestPrime[i] == i){
            grundy[i] = j++;
        } 
        grundy[i] = grundy[lowestPrime[i]];
    }

    vector< int > P(1 << MAXLOG);
    for(int i = 1; i < n; i++){
        P[grundy[i]]++;
    }

    P = power(P, k);

    cout << P[0] << endl;


	return 0;
}

