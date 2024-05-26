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


const int p = 987654321;
const int MOD = p;

lli inverse(lli a, lli n){
	lli r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	assert(r0 == 1);
	if(s0 < 0) s0 += n;
	return s0;
}

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
        lli nrev = inverse(n, p);
		for(int i = 0; i < n; ++i)
			A[i] = A[i] * nrev % p;
	}
}


typedef vector<int> Poly;
Poly power(Poly A, lli b){
    int n = SZ(A);
    Poly res(n); res[0] = 1;
    fwt(res, 2, 1);
    fwt(A, 2, 1);

    while(b){
        if(b & 1)
            forn(i, n)
                res[i] = 1LL*res[i]*A[i] % MOD;

        forn(i, n)
            A[i] = 1LL*A[i]*A[i] % MOD;

        b >>= 1;
    }

    fwt(res, 2, -1);
    return res;
}

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

const int MAX_LOG = 8;
const int MAX_GRUNDY = 45;

int main () {
	//fastIO();
    
    const int n = 1e7;
    const lli k = 1e12;
    lowestPrimeSieve(n);

    auto mex = [&](bitset<MAX_GRUNDY> mexes){
        int j = 0;
        while(mexes[j]) j++;
        return j;
    };

    vector<int> grundy(n+1);
    grundy[1] = 0;
    
    vector< set<int> > xor_divs(n+1);
    for(int i = 2; i <= n; i++){
        if(lowestPrime[i] == i){
            grundy[i] = 0;
            continue;
        }

        int gr_div = i / lowestPrime[i];

        xor_divs[i] = xor_divs[gr_div];
        xor_divs[i].insert(grundy[gr_div]);

        bitset<MAX_GRUNDY> mexes;
        forn(i, grundy[gr_div]) mexes[i] = 1;

        for(auto xor_1: xor_divs[i]){
            int xor_2 = grundy[gr_div];
            if((xor_1 ^ xor_2) >= MAX_GRUNDY) continue;

            mexes[xor_1 ^ xor_2] = 1;
        }

        grundy[i] = mex(mexes);
    }


    vector<int> P(1 << MAX_LOG);
    forr(i, 2, n) P[grundy[i]]++;

    P = power(P, k);

    int sum = 0;
    forr(i, 1, SZ(P)-1) (sum += P[i]) %= MOD;
    cout << sum << endl;

	return 0;
}

